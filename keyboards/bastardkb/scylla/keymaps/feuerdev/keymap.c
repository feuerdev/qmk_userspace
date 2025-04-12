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
    NAV,
    SYMBOL,
    FUNCTION
};

enum custom_keycodes {
    EMAIL = SAFE_RANGE,
    SW_WIN,
};

#define HOME_A LSFT_T(KC_A)
#define HOME_O RSFT_T(KC_O)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [ALPHA] = LAYOUT_split_4x6_5(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5,                  KC_6, KC_7, KC_8, KC_9, KC_0, KC_NO,
                             //-------------------------------------------------------//-----------------------------------------------------------//
                             KC_TAB, KC_Q, KC_W, KC_F, KC_P, KC_B,                      KC_J, KC_L, KC_U, KC_Y, KC_MINS, KC_NO,
                             //-------------------------------------------------------//-----------------------------------------------------------//
                             KC_LSFT, HOME_A, KC_R, KC_S, KC_T, KC_G,                   KC_M, KC_N, KC_E, KC_I, HOME_O, KC_NO,
                             //-------------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_Z, KC_X, KC_C, KC_D, KC_V,                       KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, KC_NO,
                             //-------------------------------------------------------//-----------------------------------------------------------//
                             //-------------------------------------------------------//-----------------------------------------------------------//
                             LALT_T(KC_ESC), LT(SYMBOL, KC_SPC), LGUI_T(KC_TAB),        LCTL_T(KC_ENT), LT(NAV, KC_BSPC), LT(FUNCTION, KC_DEL), 
                             //-------------------------------------------------------//-----------------------------------------------------------//
                             KC_HYPR, KC_MEH,                                           KC_NO, KC_NO),

    [NAV] = LAYOUT_split_4x6_5(KC_TRNS, HYPR(KC_1), HYPR(KC_2), HYPR(KC_3), HYPR(KC_4), HYPR(KC_5),          KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                            //-------------------------------------------------------------------------------//-----------------------------------------------------------//
                            KC_TRNS, HYPR(KC_Q), HYPR(KC_W), HYPR(KC_F), HYPR(KC_P), HYPR(KC_B),             KC_NO, LGUI(KC_GRV), KC_UP, KC_NO, KC_NO, KC_NO,
                            //-------------------------------------------------------------------------------//-----------------------------------------------------------//
                            KC_TRNS, KC_LSFT, HYPR(KC_R), HYPR(KC_S), HYPR(KC_T), HYPR(KC_G),                  KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_RSFT, KC_NO,
                            //-------------------------------------------------------------------------------//-----------------------------------------------------------//
                            KC_TRNS, HYPR(KC_Z), HYPR(KC_X), HYPR(KC_C), HYPR(KC_D), HYPR(KC_V),               KC_NO, SW_WIN, LGUI(KC_LCBR), LGUI(KC_RCBR), KC_NO, KC_NO,
                            //-------------------------------------------------------------------------------//-----------------------------------------------------------//
                            //-------------------------------------------------------------------------------//-----------------------------------------------------------//
                            LALT_T(KC_ESC), LT(SYMBOL, KC_SPC), LGUI_T(KC_TAB),                              LCTL_T(KC_ENT), KC_TRNS, LT(FUNCTION, KC_DEL),   
                            //-------------------------------------------------------------------------------//-----------------------------------------------------------//
                            KC_HYPR, KC_MEH,                                                                 KC_NO, KC_NO),

    [SYMBOL] = LAYOUT_split_4x6_5(KC_TRNS, KC_1, KC_2, KC_3, KC_4, KC_5,                 KC_6, KC_7, KC_8, KC_9, KC_0, KC_NO,
                            //-------------------------------------------------------//--------------------------------------------------------------//
                            KC_TRNS, KC_BSLS, KC_LABK, KC_RABK, KC_ASTR, KC_NO,          KC_AMPR, KC_GRV, KC_LBRC, KC_RBRC, KC_PERC, KC_NO,
                            //-------------------------------------------------------//--------------------------------------------------------------//
                            KC_TRNS, KC_TILD, KC_MINS, KC_PLUS, KC_EQL, KC_HASH,           KC_PIPE, KC_COLN, KC_LPRN, KC_RPRN, KC_SCLN, KC_NO,
                            //-------------------------------------------------------//--------------------------------------------------------------//
                            KC_TRNS, KC_CIRC, KC_SLSH, KC_DQUO, KC_QUOT, LALT_T(KC_U),     EMAIL, KC_DLR, KC_LCBR, KC_RCBR, KC_AT, KC_NO,
                            //-------------------------------------------------------//--------------------------------------------------------------//
                            //-------------------------------------------------------//-----------------------------------------------------------//
                            LALT_T(KC_ESC), KC_TRNS, LGUI_T(KC_TAB),                     LCTL_T(KC_ENT), LT(NAV, KC_BSPC), LT(FUNCTION, KC_DEL), 
                            //-------------------------------------------------------//-----------------------------------------------------------//
                            KC_HYPR, KC_MEH,                                             KC_NO, KC_NO),

    [FUNCTION] = LAYOUT_split_4x6_5(KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, QK_BOOT,
                            //----------------------------------------------------//-----------------------------------------------------------//
                            KC_TRNS, KC_F12, KC_F7, KC_F8, KC_F9, KC_NO,              KC_NO, KC_NO, KC_VOLU, KC_NO, KC_NO, QK_CLEAR_EEPROM,
                            //----------------------------------------------------//-----------------------------------------------------------//
                            KC_TRNS, KC_F11, KC_F4, KC_F5, KC_F6, KC_NO,                KC_NO, KC_MPRV, KC_VOLD, KC_MNXT, KC_NO, KC_NO,
                            //----------------------------------------------------//-----------------------------------------------------------//
                            KC_TRNS, KC_F10, KC_F1, KC_F2, KC_F3, KC_NO,                KC_NO, KC_MPLY, KC_MSTP, KC_MUTE, KC_NO, KC_NO,
                            //----------------------------------------------------//-----------------------------------------------------------//
                            //----------------------------------------------------//-----------------------------------------------------------//
                            LALT_T(KC_ESC), LT(SYMBOL, KC_SPC), LGUI_T(KC_TAB),       LCTL_T(KC_ENT), LT(NAV, KC_BSPC), KC_TRNS,
                            //----------------------------------------------------//-----------------------------------------------------------//
                            KC_HYPR, KC_MEH,                                          KC_NO, KC_NO),
};

// Define combos for bootloader and EEPROM reset
enum combo_events {
 COMBO_CAPSWORD,
 COMBO_COUNT
};

const uint16_t PROGMEM capsword_combo[] = {HOME_A, HOME_O, COMBO_END};

combo_t key_combos[] = {
 [COMBO_CAPSWORD] = COMBO(capsword_combo, QK_CAPS_WORD_TOGGLE),
};

const custom_shift_key_t custom_shift_keys[] = {
 {KC_COMM, KC_EXLM}, // Shift , is !
 {KC_DOT , KC_QUES}, // Shift . is ?
 {KC_SLSH, KC_BSLS}, // Shift forward slash is backslash
};

uint8_t NUM_CUSTOM_SHIFT_KEYS =
    sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);

bool sw_win_active = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef ENABLE_ACHORDION
    if (!process_achordion(keycode, record)) { return false; }
#endif
    if (!process_custom_shift_keys(keycode, record)) { return false; }
    update_swapper(&sw_win_active, KC_LGUI, KC_TAB, SW_WIN, keycode, record);

    switch (keycode) {
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

