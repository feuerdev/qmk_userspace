#include QMK_KEYBOARD_H
#include "features/custom_shift_keys.h"
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
    EMAIL,
    ENT_OR_BOOT,
};

enum combo_events {
    COMBO_TOGGLE_SPEED,
    COMBO_BOOTLOADER,
    COMBO_TOGGLE_QWERTZ_ON,
    COMBO_TOGGLE_QWERTZ_OFF,
    COMBO_CAPSWORD,
    COMBO_ESC,
    COMBO_CTRL_C,
    COMBO_CUT,
    COMBO_CUT_ALT,
    COMBO_COPY,
    COMBO_PASTE,
    COMBO_HASH,
    COMBO_DOLLAR,
    COMBO_LBRACKET,
    COMBO_RBRACKET,
    COMBO_LPAREN,
    COMBO_RPAREN,
    COMBO_LBRACE,
    COMBO_RBRACE,
    COMBO_EQUAL,
    COMBO_PLUS,
    COMBO_AT,
    COMBO_PERCENT,
    COMBO_PIPE,
    COMBO_TILDE,
    COMBO_GRAVE,
    COMBO_STAR,
    COMBO_CARET,
    COMBO_AMPS,
    COMBO_EMAIL,
    COMBO_AMPERSAND,
    COMBO_GRAVE_DH,
    COMBO_STAR_FU,
    COMBO_PLUS_COMMA_C,
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
        /* row 1 top     */ { XXXXX,   KC_F12,  KC_F7,   KC_F8,        KC_F9,           DPI_MOD      },
        /* row 2 middle  */ { XXXXX,   KC_F11,  KC_F4,   KC_F5,        KC_F6,           DPI_RMOD     },
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
const uint16_t PROGMEM bootloader_combo[] = {KC_COLN, KC_QUOT, COMBO_END};
const uint16_t PROGMEM qwertz_on_combo[] = {NUM_Q, NUM_MINS, COMBO_END};
const uint16_t PROGMEM qwertz_off_combo[] = {KC_Q, KC_P, COMBO_END};
const uint16_t PROGMEM capsword_combo[] = {HOME_A, HOME_O, COMBO_END};
const uint16_t PROGMEM esc_combo[] = {NUM_W, NUM_F, COMBO_END};
const uint16_t PROGMEM ctrl_c_combo[] = {NUM_Q, NUM_W, COMBO_END};
const uint16_t PROGMEM cut_combo[] = {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM cut_alt_combo[] = {KC_X, KC_D, COMBO_END};
const uint16_t PROGMEM copy_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM paste_combo[] = {KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM hash_combo[] = {HOME_T, KC_G, COMBO_END};
const uint16_t PROGMEM dollar_combo[] = {NUM_F, NUM_P, COMBO_END};
const uint16_t PROGMEM lbracket_combo[] = {NUM_L, NUM_U, COMBO_END};
const uint16_t PROGMEM rbracket_combo[] = {NUM_U, NUM_Y, COMBO_END};
const uint16_t PROGMEM lparen_combo[] = {HOME_N, HOME_E, COMBO_END};
const uint16_t PROGMEM rparen_combo[] = {HOME_E, HOME_I, COMBO_END};
const uint16_t PROGMEM lbrace_combo[] = {KC_H, KC_COMM, COMBO_END};
const uint16_t PROGMEM rbrace_combo[] = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM equal_combo[] = {HOME_S, HOME_T, COMBO_END};
const uint16_t PROGMEM plus_combo[] = {HOME_R, HOME_S, COMBO_END};
const uint16_t PROGMEM at_combo[] = {KC_M, HOME_N, COMBO_END};
const uint16_t PROGMEM percent_combo[] = {NUM_P, HOME_T, COMBO_END};
const uint16_t PROGMEM pipe_combo[] = {NUM_U, HOME_E, COMBO_END};
const uint16_t PROGMEM tilde_combo[] = {NUM_L, HOME_N, COMBO_END};
const uint16_t PROGMEM grave_combo[] = {HOME_N, KC_H, COMBO_END};
const uint16_t PROGMEM star_combo[] = {HOME_S, KC_C, COMBO_END};
const uint16_t PROGMEM caret_combo[] = {NUM_F, HOME_S, COMBO_END};
const uint16_t PROGMEM amps_combo[] = {HOME_T, KC_D, COMBO_END};
const uint16_t PROGMEM email_combo[] = {KC_G, KC_M, COMBO_END};
const uint16_t PROGMEM ampersand_combo[] = {NUM_P, NUM_L, COMBO_END};
const uint16_t PROGMEM grave_dh_combo[] = {KC_D, KC_H, COMBO_END};
const uint16_t PROGMEM star_fu_combo[] = {NUM_F, NUM_U, COMBO_END};
const uint16_t PROGMEM plus_comma_c_combo[] = {KC_COMM, KC_C, COMBO_END};

combo_t key_combos[] = {
    [COMBO_TOGGLE_SPEED] = COMBO(speed_combo, TG(SPEED)),
    [COMBO_BOOTLOADER] = COMBO(bootloader_combo, QK_BOOT),
    [COMBO_TOGGLE_QWERTZ_ON] = COMBO(qwertz_on_combo, TG(QWERTZ)),
    [COMBO_TOGGLE_QWERTZ_OFF] = COMBO(qwertz_off_combo, TG(QWERTZ)),
    [COMBO_CAPSWORD] = COMBO(capsword_combo, QK_CAPS_WORD_TOGGLE),
    [COMBO_ESC] = COMBO(esc_combo, KC_ESC),
    [COMBO_CTRL_C] = COMBO(ctrl_c_combo, LCTL(KC_C)),
    [COMBO_CUT] = COMBO(cut_combo, LGUI(KC_X)),
    [COMBO_CUT_ALT] = COMBO(cut_alt_combo, LGUI(KC_X)),
    [COMBO_COPY] = COMBO(copy_combo, LGUI(KC_C)),
    [COMBO_PASTE] = COMBO(paste_combo, LGUI(KC_V)),
    [COMBO_HASH] = COMBO(hash_combo, KC_HASH),
    [COMBO_DOLLAR] = COMBO(dollar_combo, KC_DLR),
    [COMBO_LBRACKET] = COMBO(lbracket_combo, KC_LBRC),
    [COMBO_RBRACKET] = COMBO(rbracket_combo, KC_RBRC),
    [COMBO_LPAREN] = COMBO(lparen_combo, KC_LPRN),
    [COMBO_RPAREN] = COMBO(rparen_combo, KC_RPRN),
    [COMBO_LBRACE] = COMBO(lbrace_combo, KC_LCBR),
    [COMBO_RBRACE] = COMBO(rbrace_combo, KC_RCBR),
    [COMBO_EQUAL] = COMBO(equal_combo, KC_EQL),
    [COMBO_PLUS] = COMBO(plus_combo, KC_PLUS),
    [COMBO_AT] = COMBO(at_combo, KC_AT),
    [COMBO_PERCENT] = COMBO(percent_combo, KC_PERC),
    [COMBO_PIPE] = COMBO(pipe_combo, KC_PIPE),
    [COMBO_TILDE] = COMBO(tilde_combo, KC_TILD),
    [COMBO_GRAVE] = COMBO(grave_combo, KC_GRV),
    [COMBO_STAR] = COMBO(star_combo, KC_ASTR),
    [COMBO_CARET] = COMBO(caret_combo, KC_CIRC),
    [COMBO_AMPS] = COMBO(amps_combo, KC_AMPR),
    [COMBO_EMAIL] = COMBO(email_combo, EMAIL),
    [COMBO_AMPERSAND] = COMBO(ampersand_combo, KC_AMPR),
    [COMBO_GRAVE_DH] = COMBO(grave_dh_combo, KC_GRV),
    [COMBO_STAR_FU] = COMBO(star_fu_combo, KC_ASTR),
    [COMBO_PLUS_COMMA_C] = COMBO(plus_comma_c_combo, KC_PLUS),
};

const custom_shift_key_t custom_shift_keys[] = {
    {KC_COMM, KC_EXLM},
    {KC_DOT,  KC_QUES},
    {KC_SLSH, KC_BSLS},
    {KC_COLN, KC_SCLN},
    {KC_LPRN, KC_LABK},
    {KC_RPRN, KC_RABK},
};

uint8_t NUM_CUSTOM_SHIFT_KEYS = sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);

static top_num_key_t *find_top_num_key(uint16_t keycode) {
    for (uint8_t i = 0; i < ARRAY_SIZE(top_num_keys); i++) {
        if (top_num_keys[i].keycode == keycode) {
            return &top_num_keys[i];
        }
    }
    return NULL;
}

uint16_t get_combo_term(uint16_t combo_index, combo_t *combo) {
    switch (combo_index) {
        case COMBO_BOOTLOADER:
            return COMBO_TERM_BOOT;
        case COMBO_TOGGLE_SPEED:
        case COMBO_TOGGLE_QWERTZ_ON:
        case COMBO_TOGGLE_QWERTZ_OFF:
            return COMBO_TERM_TOGGLE;
        case COMBO_ESC:
        case COMBO_GRAVE:
        case COMBO_STAR:
        case COMBO_CARET:
        case COMBO_AMPS:
        case COMBO_AMPERSAND:
        case COMBO_GRAVE_DH:
        case COMBO_STAR_FU:
        case COMBO_PLUS_COMMA_C:
            return COMBO_TERM_SLOW;
        default:
            return COMBO_TERM_FAST;
    }
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

    if (!process_custom_shift_keys(keycode, record)) {
        return false;
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

    if (keycode == EMAIL) {
        if (record->event.pressed) {
            SEND_STRING("jannik@feuer.dev");
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
