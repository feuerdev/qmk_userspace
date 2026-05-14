#include QMK_KEYBOARD_H

/*
 * Encoder-pin probe (left half).
 *
 * Right half is the known one: encoder lives on GP14 (A) and GP16 (B),
 * identified earlier because the pinprobe v3 saw matrix noise on those
 * pins when the encoder was rotated. The pinprobe v3 EXCLUDED GP14 and
 * GP16 to keep its output readable, so when the left half ran the same
 * probe and the encoder was rotated, no lines appeared. That left the
 * left-encoder wiring unknown.
 *
 * This probe sets every free GPIO (including GP14 and GP16) to
 * input-pull-up and prints every HIGH->LOW transition. Rotate the left
 * encoder; the two pins that toggle are the encoder's A and B.
 *
 * Avoided pins:
 *   - left matrix pins (GP5, GP6, GP7, GP8, GP9, GP10, GP12, GP13,
 *     GP15, GP17, GP18) -- still in use for the matrix scan that lets
 *     the probe print
 *   - GP25 (we parked SOFT_SERIAL_PIN here so the QMK split driver
 *     does not configure a candidate pin)
 *
 * To suppress idle chatter, each pin reports at most once per
 * COOLDOWN_MS. A real encoder rotation pulls both pins low repeatedly
 * and will be obvious; static-low pins (like GP11 and GP29 on the
 * master side seen earlier) get a single line and stay quiet.
 */

#define PROBE_BOOT_DELAY_MS 3000
#define COOLDOWN_MS         100

static const pin_t probe_pins[] = {
    GP0, GP1, GP2, GP3, GP4, GP11, GP14, GP16, GP19, GP20, GP21, GP22, GP23, GP26, GP27, GP28, GP29,
};
static const char *const probe_labels[] = {
    "GP0", "GP1", "GP2", "GP3", "GP4", "GP11", "GP14", "GP16", "GP19", "GP20", "GP21", "GP22", "GP23", "GP26", "GP27", "GP28", "GP29",
};
#define N_PINS (sizeof(probe_pins) / sizeof(probe_pins[0]))

static uint32_t boot_time = 0;
static bool     ready     = false;
static bool     last_low[N_PINS];
static uint32_t last_report[N_PINS];

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = {
        { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO },
        { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO },
        { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO },
        { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO },
        { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO },
        { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO },
        { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO },
        { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO },
        { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO },
        { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO },
    },
};
// clang-format on

static void print_u32(uint32_t v) {
    if (v == 0) { send_string("0"); return; }
    char tmp[12];
    uint8_t n = 0;
    while (v > 0) { tmp[n++] = '0' + (v % 10); v /= 10; }
    char out[12];
    for (uint8_t i = 0; i < n; i++) out[i] = tmp[n - 1 - i];
    out[n] = 0;
    send_string(out);
}

void keyboard_post_init_user(void) {
    boot_time = timer_read32();
    for (uint8_t i = 0; i < N_PINS; i++) {
        gpio_set_pin_input_high(probe_pins[i]);
        last_low[i]    = false;
        last_report[i] = 0;
    }
}

void housekeeping_task_user(void) {
    if (timer_elapsed32(boot_time) < PROBE_BOOT_DELAY_MS) {
        return;
    }
    if (!ready) {
        send_string("encoderprobe ready\n");
        ready = true;
        return;
    }

    uint32_t now = timer_read32();
    for (uint8_t i = 0; i < N_PINS; i++) {
        bool low = !gpio_read_pin(probe_pins[i]);
        if (low != last_low[i]) {
            last_low[i] = low;
            if (low) {
                if (last_report[i] != 0 && TIMER_DIFF_32(now, last_report[i]) < COOLDOWN_MS) {
                    continue;
                }
                last_report[i] = now == 0 ? 1 : now;
                send_string(probe_labels[i]);
                send_string(" lo t=");
                print_u32(now);
                send_string("\n");
            }
        }
    }
}
