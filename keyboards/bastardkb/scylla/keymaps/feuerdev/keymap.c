/*
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "features/custom_shift_keys.h"
#include "features/swapper.h"
#ifdef ENABLE_ACHORDION
#include "features/achordion.h"
#endif

enum layers {
    ALPHA,
    MEDIA,
    NAV,
    SYMBOL,
    FUNCTION,
    MOUSE
};

enum custom_keycodes {
    BOOT_L = SAFE_RANGE,
    BOOT_R,
    EE_RST_L,
    EE_RST_R,
    EMAIL,
    SW_WIN,
};

#define HOME_A LSFT_T(KC_A)
#define HOME_O RSFT_T(KC_O)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [ALPHA] = LAYOUT_split_4x6_5(BOOT_L, KC_1, KC_2, KC_3, KC_4, KC_5,                  KC_6, KC_7, KC_8, KC_9, KC_0, BOOT_R,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             EE_RST_L, KC_Q, KC_W, KC_F, KC_P, KC_B,                KC_J, KC_L, KC_U, KC_Y, KC_MINS, EE_RST_R,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, HOME_A, KC_R, KC_S, KC_T, KC_G,                 KC_M, KC_N, KC_E, KC_I, HOME_O, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             TG(MOUSE), KC_Z, KC_X, KC_C, KC_D, KC_V,                   KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             //-------------------------------------------------//-----------------------------------------------------------//
                             LT(MEDIA, KC_ESC), LT(NAV, KC_SPC), LGUI_T(KC_TAB),          LGUI_T(KC_ENT), LT(SYMBOL, KC_BSPC), LT(FUNCTION, KC_DEL), 
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_LCTL, KC_LALT,                                      KC_LALT, KC_HYPR),

    [MEDIA] = LAYOUT_split_4x6_5(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                            //-------------------------------------------------//-----------------------------------------------------------//
                            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                            //-------------------------------------------------//-----------------------------------------------------------//
                            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,            KC_NO, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_NO,
                            //-------------------------------------------------//-----------------------------------------------------------//
                            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                            //-------------------------------------------------//-----------------------------------------------------------//
                            //-------------------------------------------------//-----------------------------------------------------------//
                            KC_NO, KC_NO, KC_NO,                                 KC_MSTP, KC_MPLY, KC_MUTE, 
                            //-------------------------------------------------//-----------------------------------------------------------//
                            KC_LCTL, KC_LALT,                                    KC_LALT, KC_HYPR),

    [NAV] = LAYOUT_split_4x6_5(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                       KC_F13, KC_F16, KC_F17, KC_F18, KC_F19, KC_NO,
                            //---------------------------------------------------------//-----------------------------------------------------------//
                            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                        KC_NO, LGUI(KC_GRV), KC_UP, KC_NO, KC_NO, KC_NO,
                            //---------------------------------------------------------//-----------------------------------------------------------//
                            KC_NO, KC_LSFT, KC_NO, KC_NO, KC_F19, KC_NO,                     KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_RSFT, KC_NO,
                            //---------------------------------------------------------//-----------------------------------------------------------//
                            KC_NO, KC_F13, KC_F16, KC_F17, KC_F18, KC_NO,                    KC_NO, SW_WIN, LGUI(KC_LCBR), LGUI(KC_RCBR), KC_NO, KC_NO,
                            //---------------------------------------------------------//-----------------------------------------------------------//
                            //---------------------------------------------------------//-----------------------------------------------------------//
                            KC_NO, KC_NO, KC_NO,                                             LGUI_T(KC_ENT), KC_BSPC, KC_DEL,  
                            //---------------------------------------------------------//-----------------------------------------------------------//
                            KC_LCTL, KC_LALT,                                                KC_LALT, KC_HYPR),

    [SYMBOL] = LAYOUT_split_4x6_5(KC_NO, KC_1, KC_2, KC_3, KC_4, KC_5,                  KC_6, KC_7, KC_8, KC_9, KC_0, KC_NO,
                            //-------------------------------------------------//--------------------------------------------------------------//
                            KC_NO, KC_QUOT, KC_LABK, KC_RABK, KC_DQUO, KC_NO,      KC_AMPR, KC_GRV, KC_LBRC, KC_RBRC, KC_PERC, KC_NO,
                            //-------------------------------------------------//--------------------------------------------------------------//
                            KC_NO, KC_TILD, KC_MINS, KC_PLUS, KC_EQL, KC_HASH,     KC_PIPE, KC_COLN, KC_LPRN, KC_RPRN, KC_SCLN, KC_NO,
                            //-------------------------------------------------//--------------------------------------------------------------//
                            KC_NO, KC_CIRC, KC_SLSH, KC_ASTR, KC_BSLS, KC_NO,      EMAIL, KC_DLR, KC_LCBR, KC_RCBR, KC_AT, KC_NO,
                            //-------------------------------------------------//--------------------------------------------------------------//
                            //-------------------------------------------------//-----------------------------------------------------------//
                            KC_ESC, KC_SPC, LGUI_T(KC_TAB),                        KC_NO, KC_NO, KC_NO, 
                            //-------------------------------------------------//-----------------------------------------------------------//
                            KC_LCTL, KC_LALT,                                      KC_LALT, KC_HYPR),

    [FUNCTION] = LAYOUT_split_4x6_5(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                            //-------------------------------------------------//-----------------------------------------------------------//
                            KC_NO, KC_F12, KC_F7, KC_F8, KC_F9, KC_NO,             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                            //-------------------------------------------------//-----------------------------------------------------------//
                            KC_NO, KC_F11, KC_F4, KC_F5, KC_F6, KC_NO,             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                            //-------------------------------------------------//-----------------------------------------------------------//
                            KC_NO, KC_F10, KC_F1, KC_F2, KC_F3, KC_NO,             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                            //-------------------------------------------------//-----------------------------------------------------------//
                            //-------------------------------------------------//-----------------------------------------------------------//
                            KC_ESC, KC_SPC, LGUI_T(KC_TAB),                        KC_NO, KC_NO, KC_NO, 
                            //-------------------------------------------------//-----------------------------------------------------------//
                            KC_LCTL, KC_LALT,                                      KC_LALT, KC_HYPR),

    [MOUSE] = LAYOUT_split_4x6_5(KC_NO, KC_NO, KC_NO, KC_NO, LGUI(LSFT(KC_4)), LGUI(LSFT(KC_5)), TG(MOUSE), TG(MOUSE), TG(MOUSE), TG(MOUSE), TG(MOUSE), TG(MOUSE),
                             //------------------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_NO, LGUI(KC_A), LGUI(KC_Z), LGUI(LSFT(KC_Z)), KC_NO,   TG(MOUSE), TG(MOUSE), TG(MOUSE), TG(MOUSE), TG(MOUSE), TG(MOUSE),
                             //------------------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_NO,                TG(MOUSE), TG(MOUSE), TG(MOUSE), TG(MOUSE), TG(MOUSE), TG(MOUSE),
                             //------------------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_NO, LGUI(KC_X), LGUI(KC_C), LGUI(KC_V), KC_NO,         TG(MOUSE), TG(MOUSE), TG(MOUSE), TG(MOUSE), TG(MOUSE), TG(MOUSE),
                             //------------------------------------------------------------//-----------------------------------------------------------//
                             //------------------------------------------------------------//-----------------------------------------------------------//
                             KC_BSPC, KC_SPC, LGUI_T(KC_TAB),                                 TG(MOUSE), TG(MOUSE), TG(MOUSE),
                             //------------------------------------------------------------//-----------------------------------------------------------//
                             KC_LCTL, KC_LALT,                                                TG(MOUSE), TG(MOUSE)),
};

// Define combos for bootloader and EEPROM reset
enum combo_events {
 COMBO_BOOTLOADER,
 COMBO_EE_RESET,
 COMBO_CAPSWORD,
 COMBO_COUNT
};

const uint16_t PROGMEM bootloader_combo[] = {BOOT_L, BOOT_R, COMBO_END};
const uint16_t PROGMEM ee_reset_combo[] = {EE_RST_L, EE_RST_R, COMBO_END};
const uint16_t PROGMEM capsword_combo[] = {HOME_A, HOME_O, COMBO_END};

combo_t key_combos[] = {
 [COMBO_BOOTLOADER] = COMBO(bootloader_combo, QK_BOOT),
 [COMBO_EE_RESET] = COMBO(ee_reset_combo, QK_CLEAR_EEPROM),
 [COMBO_CAPSWORD] = COMBO(capsword_combo, QK_CAPS_WORD_TOGGLE),
};

const custom_shift_key_t custom_shift_keys[] = {
 {KC_COMM, KC_EXLM}, // Shift , is !
 {KC_DOT , KC_QUES}, // Shift . is ?
 {KC_SLSH, KC_BSLS}  // Shift forward slash is backslash
};

uint8_t NUM_CUSTOM_SHIFT_KEYS =
    sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);

bool sw_win_active = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef ENABLE_ACHORDION
    if (!process_achordion(keycode, record)) { return false; }
#endif
    if (!process_custom_shift_keys(keycode, record)) { return false; }
    update_swapper(
        &sw_win_active, KC_LGUI, KC_TAB, SW_WIN,
        keycode, record
    );

    switch (keycode) {
        case BOOT_L:
        case BOOT_R:
        case EE_RST_L:
        case EE_RST_R:
            // These keys do nothing on their own
            return false;
        case EMAIL:
            if (record->event.pressed) {
                SEND_STRING("jannik@feuer.dev");
            }
            return false;
        default:
            return true;
    }
}

void housekeeping_task_user(void) {
#ifdef ENABLE_ACHORDION
    achordion_task();
#endif
}

