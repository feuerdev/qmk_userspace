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
#define HOME_R LCTL_T(KC_R)
#define HOME_S LALT_T(KC_S)
#define HOME_T LGUI_T(KC_T)

#define HOME_N LGUI_T(KC_N)
#define HOME_E LALT_T(KC_E)
#define HOME_I LCTL_T(KC_I)
#define HOME_O LSFT_T(KC_O)


enum combo_events {
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
  COMBO_MINUS,
  COMBO_AT,
  COMBO_PERCENT,
  COMBO_PIPE,
  COMBO_TILDE,
  COMBO_GRAVE,
  COMBO_STAR,
  COMBO_CARET,
  COMBO_AMPS,
  COMBO_EMAIL_COMBO,
  COMBO_COUNT
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [ALPHA] = LAYOUT_split_4x6_5(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5,                  KC_6, KC_7, KC_8, KC_9, KC_0, KC_NO,
                             //-------------------------------------------------------//-----------------------------------------------------------//
                             KC_TAB, KC_Q, KC_W, KC_F, KC_P, KC_B,                      KC_J, KC_L, KC_U, KC_Y, KC_MINS, KC_NO,
                             //-------------------------------------------------------//-----------------------------------------------------------//
                             KC_COLN, HOME_A, HOME_R, HOME_S, HOME_T, KC_G,             KC_M, HOME_N, HOME_E, HOME_I, HOME_O, KC_QUOT,
                             //-------------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_Z, KC_X, KC_C, KC_D, KC_V,                       KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, KC_NO,
                             //-------------------------------------------------------//-----------------------------------------------------------//
                             //-------------------------------------------------------//-----------------------------------------------------------//
                             KC_HYPR, LT(NAV, KC_SPC), KC_TAB,                          KC_ENT, LSFT_T(KC_BSPC), LT(FUNCTION, KC_DEL), 
                             //-------------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_NO,                                              KC_NO, KC_NO),

    [NAV] = LAYOUT_split_4x6_5(KC_TRNS, HYPR(KC_1), HYPR(KC_2), HYPR(KC_3), HYPR(KC_4), HYPR(KC_5),            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                            //-------------------------------------------------------------------------------//-----------------------------------------------------------//
                            KC_TRNS, HYPR(KC_Q), HYPR(KC_W), HYPR(KC_F), HYPR(KC_P), HYPR(KC_B),               KC_NO, LGUI(KC_GRV), KC_UP, KC_NO, KC_NO, KC_NO,
                            //-------------------------------------------------------------------------------//-----------------------------------------------------------//
                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, HYPR(KC_G),                          KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_RSFT, KC_NO,
                            //-------------------------------------------------------------------------------//-----------------------------------------------------------//
                            KC_TRNS, HYPR(KC_Z), HYPR(KC_X), HYPR(KC_C), HYPR(KC_D), HYPR(KC_V),               KC_NO, SW_WIN, LGUI(KC_LCBR), LGUI(KC_RCBR), KC_NO, KC_NO,
                            //-------------------------------------------------------------------------------//-----------------------------------------------------------//
                            //-------------------------------------------------------------------------------//-----------------------------------------------------------//
                            KC_TRNS, KC_TRNS, KC_TRNS,                                                          KC_TRNS, LALT(KC_BSPC), KC_TRNS,   
                            //-------------------------------------------------------------------------------//-----------------------------------------------------------//
                            KC_TRNS, KC_TRNS,                                                                  KC_TRNS, KC_TRNS),

    [SYMBOL] = LAYOUT_split_4x6_5(KC_TRNS, KC_1, KC_2, KC_3, KC_4, KC_5,                 KC_6, KC_7, KC_8, KC_9, KC_0, KC_NO,
                            //-------------------------------------------------------//--------------------------------------------------------------//
                            KC_TRNS, KC_BSLS, KC_LABK, KC_RABK, KC_ASTR, KC_NO,          KC_AMPR, KC_GRV, KC_LBRC, KC_RBRC, KC_PERC, KC_NO,
                            //-------------------------------------------------------//--------------------------------------------------------------//
                            KC_TRNS, KC_TILD, KC_MINS, KC_PLUS, KC_EQL, KC_HASH,         KC_PIPE, KC_COLN, KC_LPRN, KC_RPRN, KC_SCLN, KC_NO,
                            //-------------------------------------------------------//--------------------------------------------------------------//
                            KC_TRNS, KC_CIRC, KC_SLSH, KC_DQUO, KC_QUOT, LALT(KC_U),     EMAIL, KC_DLR, KC_LCBR, KC_RCBR, KC_AT, KC_NO,
                            //-------------------------------------------------------//--------------------------------------------------------------//
                            //-------------------------------------------------------//-----------------------------------------------------------//
                            KC_TRNS, KC_TRNS, KC_TRNS,                                   KC_TRNS, KC_TRNS, KC_TRNS, 
                            //-------------------------------------------------------//-----------------------------------------------------------//
                            KC_TRNS, KC_TRNS,                                            KC_TRNS, KC_TRNS),

    [FUNCTION] = LAYOUT_split_4x6_5(KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, QK_BOOT,
                            //----------------------------------------------------//-----------------------------------------------------------//
                            KC_TRNS, KC_F12, KC_F7, KC_F8, KC_F9, KC_NO,              KC_NO, KC_NO, KC_VOLU, KC_NO, KC_NO, QK_CLEAR_EEPROM,
                            //----------------------------------------------------//-----------------------------------------------------------//
                            KC_TRNS, KC_F11, KC_F4, KC_F5, KC_F6, KC_NO,              KC_NO, KC_MPRV, KC_VOLD, KC_MNXT, KC_NO, KC_NO,
                            //----------------------------------------------------//-----------------------------------------------------------//
                            KC_TRNS, KC_F10, KC_F1, KC_F2, KC_F3, KC_NO,              KC_NO, KC_MPLY, KC_MSTP, KC_MUTE, KC_NO, KC_NO,
                            //----------------------------------------------------//-----------------------------------------------------------//
                            //----------------------------------------------------//-----------------------------------------------------------//
                            KC_TRNS, KC_TRNS, KC_TRNS,                                KC_TRNS, KC_TRNS, KC_TRNS,
                            //----------------------------------------------------//-----------------------------------------------------------//
                            KC_TRNS, KC_TRNS,                                         KC_TRNS, KC_TRNS),
};

// Define key combinations for each combo
const uint16_t PROGMEM capsword_combo[] = {HOME_A, HOME_O, COMBO_END};
const uint16_t PROGMEM esc_combo[] = {KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM ctrl_c_combo[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM cut_combo[] = {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM cut_alt_combo[] = {KC_X, KC_D, COMBO_END};
const uint16_t PROGMEM copy_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM paste_combo[] = {KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM hash_combo[] = {KC_T, KC_G, COMBO_END};
const uint16_t PROGMEM dollar_combo[] = {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM lbracket_combo[] = {KC_L, KC_U, COMBO_END};
const uint16_t PROGMEM rbracket_combo[] = {KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM lparen_combo[] = {HOME_N, HOME_E, COMBO_END};
const uint16_t PROGMEM rparen_combo[] = {HOME_E, HOME_I, COMBO_END};
const uint16_t PROGMEM lbrace_combo[] = {KC_H, KC_COMM, COMBO_END};
const uint16_t PROGMEM rbrace_combo[] = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM equal_combo[] = {HOME_S, HOME_T, COMBO_END};
const uint16_t PROGMEM plus_combo[] = {HOME_R, HOME_S, COMBO_END};
const uint16_t PROGMEM minus_combo[] = {HOME_A, HOME_R, COMBO_END};
const uint16_t PROGMEM at_combo[] = {KC_M, HOME_N, COMBO_END};
const uint16_t PROGMEM percent_combo[] = {KC_P, HOME_T, COMBO_END};
const uint16_t PROGMEM pipe_combo[] = {KC_U, HOME_E, COMBO_END};
const uint16_t PROGMEM tilde_combo[] = {KC_L, HOME_N, COMBO_END};
const uint16_t PROGMEM grave_combo[] = {HOME_N, KC_H, COMBO_END};
const uint16_t PROGMEM star_combo[] = {HOME_S, KC_C, COMBO_END};
const uint16_t PROGMEM caret_combo[] = {KC_F, HOME_S, COMBO_END};
const uint16_t PROGMEM amps_combo[] = {HOME_T, KC_D, COMBO_END};
const uint16_t PROGMEM email_combo[] = {HOME_E, KC_COMM, COMBO_END};

// Map the combos to their respective actions
combo_t key_combos[] = {
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
  [COMBO_MINUS] = COMBO(minus_combo, KC_MINS),
  [COMBO_AT] = COMBO(at_combo, KC_AT),
  [COMBO_PERCENT] = COMBO(percent_combo, KC_PERC),
  [COMBO_PIPE] = COMBO(pipe_combo, KC_PIPE),
  [COMBO_TILDE] = COMBO(tilde_combo, KC_TILD),
  [COMBO_GRAVE] = COMBO(grave_combo, KC_GRV),
  [COMBO_STAR] = COMBO(star_combo, KC_ASTR),
  [COMBO_CARET] = COMBO(caret_combo, KC_CIRC),
  [COMBO_AMPS] = COMBO(amps_combo, KC_AMPR),
  [COMBO_EMAIL_COMBO] = COMBO_ACTION(email_combo),
};

const custom_shift_key_t custom_shift_keys[] = {
 {KC_COMM, KC_EXLM}, // Shift , is !
 {KC_DOT , KC_QUES}, // Shift . is ?
 {KC_SLSH, KC_BSLS}, // Shift forward slash is backslash
 {KC_COLN, KC_SCLN}, // Shift : is ;
 {KC_LPRN, KC_LABK}, // Shift ( is <
 {KC_RPRN, KC_RABK}, // Shift ) is >
};

uint8_t NUM_CUSTOM_SHIFT_KEYS =
    sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);

// Process combo events
void process_combo_event(uint16_t combo_index, bool pressed) {
    switch(combo_index) {
        case COMBO_EMAIL_COMBO:
            if (pressed) {
                SEND_STRING("jannik@feuer.dev");
            }
            break;
    }
}

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

