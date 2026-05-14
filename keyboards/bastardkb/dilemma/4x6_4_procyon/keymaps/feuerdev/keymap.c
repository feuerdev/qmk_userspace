#include QMK_KEYBOARD_H
#include "split_util.h"

enum layers {
    BASE = 0,
    NAV,
    FUNC,
    NUM,
    QWERTZ,
    SPEED,
};

enum custom_keycodes {
    NUM_Q = SAFE_RANGE,
    NUM_W,
    NUM_F,
    NUM_P,
    NUM_B,
    NUM_J,
    NUM_L,
    NUM_U,
    NUM_Y,
    NUM_MINS,
    ENT_OR_BOOT,
};

enum combo_events {
    COMBO_TOGGLE_SPEED,
    COMBO_COUNT,
};

#define XXXXX KC_NO
#define TOP_NUM_TERM 300

#define HOME_A LSFT_T(KC_A)
#define HOME_R LCTL_T(KC_R)
#define HOME_S LALT_T(KC_S)
#define HOME_T LGUI_T(KC_T)

#define HOME_N LGUI_T(KC_N)
#define HOME_E LALT_T(KC_E)
#define HOME_I LCTL_T(KC_I)
#define HOME_O LSFT_T(KC_O)

typedef struct {
    uint16_t keycode;
    uint16_t tap;
    uint16_t hold;
    bool     pressed;
    bool     held;
    uint16_t timer;
} top_num_key_t;

static top_num_key_t top_num_keys[] = {
    {NUM_Q,    KC_Q,    KC_1, false, false, 0},
    {NUM_W,    KC_W,    KC_2, false, false, 0},
    {NUM_F,    KC_F,    KC_3, false, false, 0},
    {NUM_P,    KC_P,    KC_4, false, false, 0},
    {NUM_B,    KC_B,    KC_5, false, false, 0},
    {NUM_J,    KC_J,    KC_6, false, false, 0},
    {NUM_L,    KC_L,    KC_7, false, false, 0},
    {NUM_U,    KC_U,    KC_8, false, false, 0},
    {NUM_Y,    KC_Y,    KC_9, false, false, 0},
    {NUM_MINS, KC_MINS, KC_0, false, false, 0},
};

static bool     ent_or_boot_pressed     = false;
static bool     ent_or_boot_interrupted = false;
static uint16_t ent_or_boot_timer       = 0;

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = {
        // LEFT
        /* row 0 phantom */ { XXXXX,   XXXXX,   XXXXX,   XXXXX,        XXXXX,           XXXXX        },
        /* row 1 top     */ { XXXXX,   NUM_Q,   NUM_W,   NUM_F,        NUM_P,           NUM_B        },
        /* row 2 middle  */ { XXXXX,   HOME_A,  HOME_R,  HOME_S,       HOME_T,          KC_G         },
        /* row 3 bottom  */ { KC_COLN, KC_Z,    KC_X,    KC_C,         KC_D,            KC_V         },
        /* row 4 thumbs  */ { XXXXX,   XXXXX,   XXXXX,   KC_HYPR,      LT(NAV, KC_SPC), KC_TAB       },
        // RIGHT (col 0 = outer pinky, col 5 = inner index)
        /* row 5 phantom */ { XXXXX,   XXXXX,   XXXXX,   XXXXX,        XXXXX,           XXXXX        },
        /* row 6 top     */ { XXXXX,   NUM_MINS, NUM_Y,  NUM_U,        NUM_L,           NUM_J        },
        /* row 7 middle  */ { XXXXX,   HOME_O,  HOME_I,  HOME_E,       HOME_N,          KC_M         },
        /* row 8 bottom  */ { KC_QUOT, KC_SLSH, KC_DOT,  KC_COMM,      KC_H,            KC_K         },
        /* row 9 thumbs  */ { XXXXX,   XXXXX,   XXXXX,   LT(FUNC, KC_DEL), LSFT_T(KC_BSPC), ENT_OR_BOOT    },
    },

    [NAV] = {
        // LEFT
        /* row 0 phantom */ { XXXXX,   XXXXX,   XXXXX,   XXXXX,        XXXXX,           XXXXX        },
        /* row 1 top     */ { XXXXX,   HYPR(KC_Q), HYPR(KC_W), HYPR(KC_F), HYPR(KC_P),  HYPR(KC_B)   },
        /* row 2 middle  */ { XXXXX,   KC_LSFT, KC_LCTL, KC_LALT,      KC_LGUI,         HYPR(KC_G)   },
        /* row 3 bottom  */ { HYPR(KC_SCLN), HYPR(KC_Z), HYPR(KC_X), HYPR(KC_C), HYPR(KC_D), HYPR(KC_V) },
        /* row 4 thumbs  */ { XXXXX,   XXXXX,   XXXXX,   KC_TRNS,      KC_TRNS,         KC_TRNS      },
        // RIGHT
        /* row 5 phantom */ { XXXXX,   XXXXX,   XXXXX,   XXXXX,        XXXXX,           XXXXX        },
        /* row 6 top     */ { XXXXX,   XXXXX,   HYPR(KC_Y), KC_UP,     LGUI(KC_GRV),    HYPR(KC_J)   },
        /* row 7 middle  */ { XXXXX,   HYPR(KC_O), KC_RGHT, KC_DOWN,   KC_LEFT,         HYPR(KC_M)   },
        /* row 8 bottom  */ { XXXXX,   XXXXX,   LGUI(KC_RBRC), LGUI(KC_LBRC), XXXXX,    XXXXX        },
        /* row 9 thumbs  */ { XXXXX,   XXXXX,   XXXXX,   KC_TRNS,      LALT(KC_BSPC),   S(KC_ENT)    },
    },

    [FUNC] = {
        // LEFT
        /* row 0 phantom */ { XXXXX,   XXXXX,   XXXXX,   XXXXX,        XXXXX,           XXXXX        },
        /* row 1 top     */ { XXXXX,   KC_F12,  KC_F7,   KC_F8,        KC_F9,           XXXXX        },
        /* row 2 middle  */ { XXXXX,   KC_F11,  KC_F4,   KC_F5,        KC_F6,           XXXXX        },
        /* row 3 bottom  */ { QK_BOOT, KC_F10,  KC_F1,   KC_F2,        KC_F3,           XXXXX        },
        /* row 4 thumbs  */ { XXXXX,   XXXXX,   XXXXX,   KC_TRNS,      KC_TRNS,         KC_TRNS      },
        // RIGHT
        /* row 5 phantom */ { XXXXX,   XXXXX,   XXXXX,   XXXXX,        XXXXX,           XXXXX        },
        /* row 6 top     */ { XXXXX,   XXXXX,   XXXXX,   KC_VOLU,      XXXXX,           XXXXX        },
        /* row 7 middle  */ { XXXXX,   XXXXX,   KC_MNXT, KC_VOLD,      KC_MPRV,         XXXXX        },
        /* row 8 bottom  */ { QK_BOOT, XXXXX,   KC_MUTE, KC_MSTP,      KC_MPLY,         XXXXX        },
        /* row 9 thumbs  */ { XXXXX,   XXXXX,   XXXXX,   KC_TRNS,      KC_TRNS,         KC_TRNS      },
    },

    [NUM] = {
        // LEFT
        /* row 0 phantom */ { XXXXX,   XXXXX,   XXXXX,   XXXXX,        XXXXX,           XXXXX        },
        /* row 1 top     */ { XXXXX,   KC_TRNS, KC_7,    KC_8,         KC_9,            KC_TRNS      },
        /* row 2 middle  */ { XXXXX,   KC_0,    KC_4,    KC_5,         KC_6,            KC_TRNS      },
        /* row 3 bottom  */ { XXXXX,   KC_0,    KC_1,    KC_2,         KC_3,            KC_TRNS      },
        /* row 4 thumbs  */ { XXXXX,   XXXXX,   XXXXX,   KC_TRNS,      KC_TRNS,         KC_TRNS      },
        // RIGHT
        /* row 5 phantom */ { XXXXX,   XXXXX,   XXXXX,   XXXXX,        XXXXX,           XXXXX        },
        /* row 6 top     */ { XXXXX,   XXXXX,   XXXXX,   XXXXX,        XXXXX,           XXXXX        },
        /* row 7 middle  */ { XXXXX,   XXXXX,   XXXXX,   XXXXX,        XXXXX,           XXXXX        },
        /* row 8 bottom  */ { XXXXX,   XXXXX,   XXXXX,   XXXXX,        XXXXX,           XXXXX        },
        /* row 9 thumbs  */ { XXXXX,   XXXXX,   XXXXX,   KC_TRNS,      KC_TRNS,         KC_TRNS      },
    },

    [QWERTZ] = {
        // LEFT
        /* row 0 phantom */ { XXXXX,   XXXXX,   XXXXX,   XXXXX,        XXXXX,           XXXXX        },
        /* row 1 top     */ { XXXXX,   KC_Q,    KC_W,    KC_E,         KC_R,            KC_T         },
        /* row 2 middle  */ { XXXXX,   KC_A,    KC_S,    KC_D,         KC_F,            KC_G         },
        /* row 3 bottom  */ { KC_LSFT, KC_Z,    KC_X,    KC_C,         KC_V,            KC_B         },
        /* row 4 thumbs  */ { XXXXX,   XXXXX,   XXXXX,   KC_LCTL,      KC_SPC,          KC_TAB       },
        // RIGHT
        /* row 5 phantom */ { XXXXX,   XXXXX,   XXXXX,   XXXXX,        XXXXX,           XXXXX        },
        /* row 6 top     */ { XXXXX,   KC_P,    KC_O,    KC_I,         KC_U,            KC_Y         },
        /* row 7 middle  */ { XXXXX,   KC_SCLN, KC_L,    KC_K,         KC_J,            KC_H         },
        /* row 8 bottom  */ { KC_QUOT, KC_MINS, KC_DOT,  KC_COMM,      KC_M,            KC_N         },
        /* row 9 thumbs  */ { XXXXX,   XXXXX,   XXXXX,   KC_DEL,       KC_BSPC,         KC_ENT       },
    },

    [SPEED] = {
        // LEFT
        /* row 0 phantom */ { XXXXX,   XXXXX,   XXXXX,   XXXXX,        XXXXX,           XXXXX        },
        /* row 1 top     */ { XXXXX,   KC_Q,    KC_W,    KC_F,         KC_P,            KC_B         },
        /* row 2 middle  */ { XXXXX,   KC_A,    KC_R,    KC_S,         KC_T,            KC_G         },
        /* row 3 bottom  */ { KC_COLN, KC_Z,    KC_X,    KC_C,         KC_D,            KC_V         },
        /* row 4 thumbs  */ { XXXXX,   XXXXX,   XXXXX,   KC_HYPR,      KC_SPC,          KC_TAB       },
        // RIGHT
        /* row 5 phantom */ { XXXXX,   XXXXX,   XXXXX,   XXXXX,        XXXXX,           XXXXX        },
        /* row 6 top     */ { XXXXX,   KC_MINS, KC_Y,    KC_U,         KC_L,            KC_J         },
        /* row 7 middle  */ { XXXXX,   KC_O,    KC_I,    KC_E,         KC_N,            KC_M         },
        /* row 8 bottom  */ { KC_QUOT, KC_SLSH, KC_DOT,  KC_COMM,      KC_H,            KC_K         },
        /* row 9 thumbs  */ { XXXXX,   XXXXX,   XXXXX,   KC_DEL,       KC_BSPC,         KC_ENT       },
    },
};
// clang-format on

const uint16_t PROGMEM speed_combo[] = {KC_Z, KC_SLSH, COMBO_END};

combo_t key_combos[] = {
    [COMBO_TOGGLE_SPEED] = COMBO(speed_combo, TG(SPEED)),
};

static top_num_key_t *find_top_num_key(uint16_t keycode) {
    for (uint8_t i = 0; i < ARRAY_SIZE(top_num_keys); i++) {
        if (top_num_keys[i].keycode == keycode) {
            return &top_num_keys[i];
        }
    }
    return NULL;
}

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    if (combo_index == COMBO_TOGGLE_SPEED) {
        return true;
    }
    return !layer_state_is(SPEED);
}

char chordal_hold_handedness(keypos_t key) {
    return key.row < MATRIX_ROWS / 2 ? 'L' : 'R';
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (ent_or_boot_pressed && record->event.pressed && keycode != ENT_OR_BOOT) {
        ent_or_boot_interrupted = true;
    }

    top_num_key_t *top_num_key = find_top_num_key(keycode);
    if (top_num_key != NULL) {
        if (record->event.pressed) {
            top_num_key->pressed = true;
            top_num_key->held    = false;
            top_num_key->timer   = timer_read();
        } else {
            if (!top_num_key->held) {
                tap_code16(top_num_key->tap);
            }
            top_num_key->pressed = false;
        }
        return false;
    }

    if (keycode == ENT_OR_BOOT) {
        if (record->event.pressed) {
            if (is_transport_connected()) {
                ent_or_boot_pressed     = true;
                ent_or_boot_interrupted = false;
                ent_or_boot_timer       = timer_read();
                layer_on(NUM);
            } else {
                reset_keyboard();
            }
        } else {
            if (ent_or_boot_pressed) {
                layer_off(NUM);
                if (!ent_or_boot_interrupted && timer_elapsed(ent_or_boot_timer) < TAPPING_TERM) {
                    tap_code(KC_ENT);
                }
            }
            ent_or_boot_pressed = false;
        }
        return false;
    }

    return true;
}

void matrix_scan_user(void) {
    for (uint8_t i = 0; i < ARRAY_SIZE(top_num_keys); i++) {
        if (top_num_keys[i].pressed && !top_num_keys[i].held && timer_elapsed(top_num_keys[i].timer) >= TOP_NUM_TERM) {
            tap_code16(top_num_keys[i].hold);
            top_num_keys[i].held = true;
        }
    }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        tap_code(clockwise ? KC_VOLU : KC_VOLD);
    } else if (index == 1) {
        tap_code(clockwise ? KC_PGDN : KC_PGUP);
    }
    return false;
}
