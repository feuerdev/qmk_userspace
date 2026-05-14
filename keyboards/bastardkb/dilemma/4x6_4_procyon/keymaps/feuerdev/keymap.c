#include QMK_KEYBOARD_H
#include "split_util.h"

/*
 * Testing keymap.
 *
 * Alpha order ported from the personal Totem ZMK config (base_layer in
 * ../zmk-config-totem/config/totem.keymap). No home-row mods, combos,
 * hold-taps, or symbol layers yet -- just plain alphas to validate that
 * every key on both halves routes to the expected character.
 *
 * We bypass the LAYOUT macro and address the matrix directly so the
 * innermost thumb on each half (matrix[4][5] and matrix[9][5], which
 * upstream's LAYOUT does not expose) becomes addressable.
 *
 * Split matrix layout (MATRIX_ROWS = 10, MATRIX_COLS = 6):
 *   rows 0..4 = LEFT  (phantom, top, middle, bottom, thumb)
 *   rows 5..9 = RIGHT (phantom, top, middle, bottom, thumb)
 *   col 0     = outer pinky on both halves (mirrored)
 *   col 5     = inner index on both halves
 *
 * The clone only has 3 alpha rows + 3 thumbs per side, so:
 *   - rows 0 and 5 are the phantom row (no switches)
 *   - thumbs occupy cols 3 (outer), 4 (middle), 5 (inner); cols 0-2 of
 *     the thumb row are empty.
 *
 * Totem alpha layer (5 cols per side; we have 6, so col 0 on each side
 * is an extra outer key not present on Totem):
 *
 *   Q  W  F  P  B  |  J  L  U  Y  -
 *   A  R  S  T  G  |  M  N  E  I  O
 *   Z  X  C  D  V  |  K  H  ,  .  /
 *
 * Outer extra columns (0) get practical defaults so the keymap is
 * usable for testing without modifying upstream.
 *
 * Thumbs (Totem-flavored):
 *   left  outer->inner = LGUI, SPC,  TAB
 *   right inner->outer = ENT,  BSPC, DEL
 */

enum layers {
    LAYER_BASE = 0,
};

enum custom_keycodes {
    ENT_OR_BOOT = SAFE_RANGE,
};

#define XXXXX KC_NO

/*
 * Debug shortcut: bottom outer-pinky on each half flashes the half that
 * currently holds USB, no case disassembly needed. To flash both halves:
 *   1. USB on right, press right bottom outer-pinky -> right in bootloader.
 *   2. Drop UF2, right reboots.
 *   3. Move USB to left, press left bottom outer-pinky -> left in bootloader.
 *   4. Drop UF2, left reboots.
 * QK_BOOT only ever reboots the master (USB-connected) half.
 *
 * MASTER_RIGHT remap: with both halves connected, "right bottom outer-pinky"
 * is matrix[8][0] = QK_BOOT. But when the LEFT half is plugged in solo, it
 * becomes master and uses the _RIGHT pin map, so its physical bottom outer-
 * pinky lands at matrix[9][5] -- which would normally be KC_ENT (right inner
 * thumb). ENT_OR_BOOT below resolves that at press time: it sends KC_ENT
 * when the split transport is up and QK_BOOT when it is not.
 *
 * Side effect: in right-solo mode, the right inner thumb also fires QK_BOOT
 * instead of ENT. Acceptable -- solo mode is for flashing, not typing.
 */

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_BASE] = {
        // LEFT
        /* row 0 phantom */ { XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX   },
        /* row 1 top     */ { KC_ESC,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B    },
        /* row 2 middle  */ { KC_LSFT, KC_A,    KC_R,    KC_S,    KC_T,    KC_G    },
        /* row 3 bottom  */ { QK_BOOT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V    },
        /* row 4 thumbs  */ { XXXXX,   XXXXX,   XXXXX,   KC_LGUI, KC_SPC,  KC_TAB  },
        // RIGHT (col 0 = outer pinky, col 5 = inner index)
        /* row 5 phantom */ { XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX   },
        /* row 6 top     */ { KC_BSLS, KC_MINS, KC_Y,    KC_U,    KC_L,    KC_J    },
        /* row 7 middle  */ { KC_QUOT, KC_O,    KC_I,    KC_E,    KC_N,    KC_M    },
        /* row 8 bottom  */ { QK_BOOT, KC_SLSH, KC_DOT,  KC_COMM, KC_H,    KC_K    },
        /* row 9 thumbs  */ { XXXXX,   XXXXX,   XXXXX,   KC_DEL,  KC_BSPC, ENT_OR_BOOT },
    },
};
// clang-format on

/*
 * Encoders: index 0 = left, index 1 = right. Both wired to GP14/GP16
 * (see config.h). Bind to volume on the left and page-up/down on the
 * right so each side is distinguishable during testing.
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == ENT_OR_BOOT) {
        if (record->event.pressed) {
            if (is_transport_connected()) {
                register_code(KC_ENT);
            } else {
                reset_keyboard();
            }
        } else {
            unregister_code(KC_ENT);
        }
        return false;
    }
    return true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        tap_code(clockwise ? KC_VOLU : KC_VOLD);
    } else if (index == 1) {
        tap_code(clockwise ? KC_PGDN : KC_PGUP);
    }
    return false;
}
