#include QMK_KEYBOARD_H

/*
 * Split-pin probe.
 *
 * Goal: identify which RP2040 pin(s) are physically wired between the two
 * halves across the clone's USB-C interhalf cable.
 *
 * Roles (decided by is_keyboard_master(); USB-connected half is master):
 *   - Slave: cycles through a set of candidate pins, driving each LOW for
 *     a fixed slot. The first pin gets a longer "sync" pulse so the
 *     master can lock onto cycle boundaries.
 *   - Master: keeps all candidates as input-pullup and prints every
 *     HIGH->LOW and LOW->HIGH transition with a timestamp.
 *
 * Avoided pins: matrix (GP5..GP10, GP12, GP13, GP15, GP17, GP18) and
 * encoder (GP14, GP16). The remaining free RP2040 GPIOs are tested.
 *
 * Interpretation: align master timestamps to slave schedule. Slave starts
 * its cycle by holding candidates[0] LOW for SYNC_MS. Each subsequent
 * candidate is driven LOW for SLOT_LOW_MS with SLOT_GAP_MS of release in
 * between. A master pin that mirrors a slave pin tells us those two
 * GPIOs are wired together across the cable.
 */

#define PROBE_BOOT_DELAY_MS 5000
#define SYNC_MS             1000
#define SLOT_LOW_MS         200
#define SLOT_GAP_MS         100

static const pin_t candidates[] = {
    GP0, GP1, GP2, GP3, GP4, GP11, GP19, GP20, GP21, GP22, GP23, GP26, GP27, GP28, GP29,
};
static const char *const candidate_labels[] = {
    "GP0", "GP1", "GP2", "GP3", "GP4", "GP11", "GP19", "GP20", "GP21", "GP22", "GP23", "GP26", "GP27", "GP28", "GP29",
};
#define N_CAND (sizeof(candidates) / sizeof(candidates[0]))

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

static uint32_t boot_time   = 0;
static bool     role_logged = false;
static bool     is_master   = false;

// Slave state.
static uint32_t slave_phase_start = 0;
static int8_t   slave_slot        = -1; // -1 = sync; 0..N_CAND-2 = candidates[slot+1]

// Master state.
static bool     last_low[N_CAND];

static void release_all_candidates_input(void) {
    for (uint8_t i = 0; i < N_CAND; i++) {
        gpio_set_pin_input_high(candidates[i]);
    }
}

static void drive_candidate_low(uint8_t idx) {
    release_all_candidates_input();
    gpio_set_pin_output(candidates[idx]);
    gpio_write_pin_low(candidates[idx]);
}

static void print_u32(uint32_t v) {
    char buf[12];
    uint8_t n = 0;
    if (v == 0) { send_string("0"); return; }
    char tmp[12];
    while (v > 0) { tmp[n++] = '0' + (v % 10); v /= 10; }
    for (uint8_t i = 0; i < n; i++) buf[i] = tmp[n - 1 - i];
    buf[n] = 0;
    send_string(buf);
}

void keyboard_post_init_user(void) {
    boot_time = timer_read32();
    release_all_candidates_input();
    for (uint8_t i = 0; i < N_CAND; i++) last_low[i] = false;
}

void housekeeping_task_user(void) {
    if (timer_elapsed32(boot_time) < PROBE_BOOT_DELAY_MS) {
        return;
    }

    if (!role_logged) {
        is_master = is_keyboard_master();
        send_string(is_master ? "splitprobe: master\n" : "splitprobe: slave\n");
        role_logged       = true;
        slave_phase_start = timer_read32();
        slave_slot        = -1;
        if (!is_master) {
            drive_candidate_low(0); // sync pulse on candidates[0]
        }
        return;
    }

    uint32_t now = timer_read32();

    if (is_master) {
        for (uint8_t i = 0; i < N_CAND; i++) {
            bool low = !gpio_read_pin(candidates[i]);
            if (low != last_low[i]) {
                last_low[i] = low;
                send_string("m ");
                send_string(candidate_labels[i]);
                send_string(low ? " lo t=" : " hi t=");
                print_u32(now);
                send_string("\n");
            }
        }
        return;
    }

    // Slave: advance schedule.
    uint32_t elapsed = timer_elapsed32(slave_phase_start);

    if (slave_slot == -1) {
        if (elapsed >= SYNC_MS) {
            release_all_candidates_input();
            slave_phase_start = now;
            slave_slot        = 0;
        }
        return;
    }

    // For each non-sync slot we have SLOT_GAP_MS released, then SLOT_LOW_MS driven low.
    uint8_t cand_idx = (uint8_t)slave_slot + 1; // candidates[1..N_CAND-1]
    if (cand_idx >= N_CAND) {
        // End of cycle: restart with sync.
        slave_phase_start = now;
        slave_slot        = -1;
        drive_candidate_low(0);
        send_string("s cycle\n");
        return;
    }

    if (elapsed < SLOT_GAP_MS) {
        // gap: keep released
        return;
    }
    if (elapsed < (uint32_t)(SLOT_GAP_MS + SLOT_LOW_MS)) {
        // drive low (idempotent if already driving)
        if (!gpio_read_pin(candidates[cand_idx])) {
            // already low; ensure it stays driven
        }
        drive_candidate_low(cand_idx);
        return;
    }

    // slot done; release and move on
    release_all_candidates_input();
    slave_phase_start = now;
    slave_slot++;
}
