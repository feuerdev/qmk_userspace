#include QMK_KEYBOARD_H

typedef struct {
    pin_t       pin;
    const char *label;
} probe_pin_t;

// GP14 and GP16 are the right-half rotary encoder pins on this clone; they
// produce false positives because the encoder hardware pulls them to GND
// independently of the probe drive. Exclude them from candidates.
static const probe_pin_t probe_pins[] = {
    {GP0, "GP0"},
    {GP1, "GP1"},
    {GP4, "GP4"},
    {GP5, "GP5"},
    {GP6, "GP6"},
    {GP7, "GP7"},
    {GP8, "GP8"},
    {GP9, "GP9"},
    {GP10, "GP10"},
    {GP11, "GP11"},
    {GP12, "GP12"},
    {GP13, "GP13"},
    {GP15, "GP15"},
    {GP17, "GP17"},
    {GP18, "GP18"},
    {GP20, "GP20"},
    {GP21, "GP21"},
    {GP22, "GP22"},
    {GP23, "GP23"},
    {GP26, "GP26"},
    {GP27, "GP27"},
    {GP28, "GP28"},
};

#define PROBE_COOLDOWN_MS 500

static uint32_t probe_start_timer = 0;
static uint32_t probe_report_timer = 0;
static bool     probe_ready_sent  = false;
static uint32_t probe_last_report[ARRAY_SIZE(probe_pins)][ARRAY_SIZE(probe_pins)];

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
};
// clang-format on

static void probe_release_pins(void) {
    for (uint8_t i = 0; i < ARRAY_SIZE(probe_pins); i++) {
        gpio_set_pin_input_high(probe_pins[i].pin);
    }
}

static void probe_report(const char *drive, const char *sense) {
    send_string("matrix ");
    send_string(drive);
    send_string(" -> ");
    send_string(sense);
    send_string("\n");
}

static bool probe_ignore_pair(uint8_t drive, uint8_t sense) {
    return (probe_pins[drive].pin == GP0 && probe_pins[sense].pin == GP11) || (probe_pins[drive].pin == GP11 && probe_pins[sense].pin == GP0);
}

void keyboard_post_init_user(void) {
    probe_start_timer = timer_read32();
    probe_release_pins();
}

void matrix_scan_user(void) {
    if (timer_elapsed32(probe_start_timer) < 3000) {
        return;
    }

    if (!probe_ready_sent) {
        send_string("pinprobe v3 ready\n");
        probe_ready_sent   = true;
        probe_report_timer = timer_read32();
        return;
    }

    if (timer_elapsed32(probe_report_timer) < 50) {
        return;
    }

    uint32_t now = timer_read32();

    for (uint8_t drive = 0; drive < ARRAY_SIZE(probe_pins); drive++) {
        probe_release_pins();
        gpio_set_pin_output(probe_pins[drive].pin);
        gpio_write_pin_low(probe_pins[drive].pin);
        wait_us(200);

        for (uint8_t sense = 0; sense < ARRAY_SIZE(probe_pins); sense++) {
            if (sense == drive) {
                continue;
            }

            if (probe_ignore_pair(drive, sense)) {
                continue;
            }

            if (probe_last_report[drive][sense] != 0 && TIMER_DIFF_32(now, probe_last_report[drive][sense]) < PROBE_COOLDOWN_MS) {
                continue;
            }

            if (gpio_read_pin(probe_pins[sense].pin)) {
                continue;
            }

            // Settle and re-read to reject momentary glitches.
            wait_us(150);
            if (gpio_read_pin(probe_pins[sense].pin)) {
                continue;
            }

            // Verify: release the drive to input-pull-up. If sense stays low,
            // an external pull-down (e.g. encoder contact) is responsible, not
            // a real matrix short to this drive. Reject.
            gpio_set_pin_input_high(probe_pins[drive].pin);
            wait_us(200);
            bool sense_still_low = !gpio_read_pin(probe_pins[sense].pin);

            // Restore drive low for any subsequent inner-loop iterations.
            gpio_set_pin_output(probe_pins[drive].pin);
            gpio_write_pin_low(probe_pins[drive].pin);
            wait_us(50);

            if (sense_still_low) {
                continue;
            }

            probe_last_report[drive][sense] = now == 0 ? 1 : now;
            probe_report(probe_pins[drive].label, probe_pins[sense].label);
            probe_report_timer = timer_read32();
            probe_release_pins();
            return;
        }
    }

    probe_release_pins();
}
