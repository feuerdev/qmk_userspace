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

 // Homerow mods definitions for CAGS (Ctrl, Alt, GUI, Shift)
 #define HOME_A LCTL_T(KC_A)
 #define HOME_R LALT_T(KC_R)
 #define HOME_S LGUI_T(KC_S)
 #define HOME_T LSFT_T(KC_T)
 
 // Reversed order on the right hand to mirror left hand (SGAC)
 #define HOME_N RSFT_T(KC_N)
 #define HOME_E RGUI_T(KC_E)
 #define HOME_I LALT_T(KC_I)
 #define HOME_O RCTL_T(KC_O)
 
 // Define custom keycodes
 enum custom_keycodes {
     BOOT_L = SAFE_RANGE,
     BOOT_R,
     EE_RST_L,
     EE_RST_R,
 };
 
 const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 
     // 0 - Alpha layer
     [0] = LAYOUT_split_4x6_5(BOOT_L, KC_1, KC_2, KC_3, KC_4, KC_5,                  KC_6, KC_7, KC_8, KC_9, KC_0, BOOT_R,
                              //-------------------------------------------------//-----------------------------------------------------------//
                              EE_RST_L, KC_Q, KC_W, KC_F, KC_P, KC_B,                KC_J, KC_L, KC_U, KC_Y, KC_SCLN, EE_RST_R,
                              //-------------------------------------------------//-----------------------------------------------------------//
                              KC_NO, HOME_A, HOME_R, HOME_S, HOME_T, KC_G,          KC_M, HOME_N, HOME_E, HOME_I, HOME_O, KC_NO,
                              //-------------------------------------------------//-----------------------------------------------------------//
                              KC_NO, KC_Z, KC_X, KC_C, KC_D, KC_V,                  KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, KC_NO,
                              //-------------------------------------------------//-----------------------------------------------------------//
                              //-------------------------------------------------//-----------------------------------------------------------//
                              LT(1, KC_ESC), LT(2, KC_SPC), LT(3, KC_TAB),          LT(4, KC_ENT), LT(5, KC_BSPC), LT(6, KC_DEL), 
                              //-------------------------------------------------//-----------------------------------------------------------//
                              QK_CAPS_WORD_TOGGLE, KC_NO,                           KC_NO, TG(7)),
 
     // 1 - Media layer
     [1] = LAYOUT_split_4x6_5(KC_NO, KC_F13, KC_F14, KC_F15, KC_F16, KC_F17,      KC_F18, KC_F19, KC_F20, KC_F21, KC_F22, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_NO,    KC_NO, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_NO, KC_NO,                                 KC_MSTP, KC_MPLY, KC_MUTE, 
                             //-------------------------------------------------//-----------------------------------------------------------//
                             QK_CAPS_WORD_TOGGLE, KC_NO,                          KC_NO, KC_NO),
 
     // 2 - Nav layer
     [2] = LAYOUT_split_4x6_5(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,           KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,            KC_NO, KC_NO, LGUI(KC_GRV), LGUI(KC_TAB), LGUI(S(KC_TAB)), KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_NO,    KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,            KC_NO, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_NO, KC_NO,                                 KC_ENT, KC_BSPC, KC_DEL,  
                             //-------------------------------------------------//-----------------------------------------------------------//
                             QK_CAPS_WORD_TOGGLE, KC_NO,                          KC_NO, KC_NO),
 
     // 3 - Mouse layer
     [3] = LAYOUT_split_4x6_5(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,           KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_NO,    KC_NO, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,            KC_NO, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_NO, KC_NO,                                 KC_BTN2, KC_BTN1, KC_BTN3,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             QK_CAPS_WORD_TOGGLE, KC_NO,                          KC_NO, KC_NO),
 
     // 4 - Symbol 2 layer
     [4] = LAYOUT_split_4x6_5(KC_NO, KC_1, KC_2, KC_3, KC_4, KC_5,                KC_6, KC_7, KC_8, KC_9, KC_0, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_QUOT, KC_LT, KC_GT, KC_DQUO, KC_DOT,       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_EXLM, KC_MINS, KC_PLUS, KC_EQL, KC_HASH,   KC_NO, KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_CIRC, KC_SLSH, KC_ASTR, KC_BSLS, KC_GRV,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_ESC, KC_SPC, KC_TAB,                              KC_NO, KC_NO, KC_NO, 
                             //-------------------------------------------------//-----------------------------------------------------------//
                             QK_CAPS_WORD_TOGGLE, KC_NO,                          KC_NO, KC_NO),
     // 5 - Symbol 1 layer
     [5] = LAYOUT_split_4x6_5(KC_NO, KC_1, KC_2, KC_3, KC_4, KC_5,                  KC_6, KC_7, KC_8, KC_9, KC_0, KC_NO,
                             //-------------------------------------------------//--------------------------------------------------------------//
                             KC_NO, KC_PERC, KC_LBRC, KC_RBRC, KC_UNDS, KC_AMPR,    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                             //-------------------------------------------------//--------------------------------------------------------------//
                             KC_NO, KC_QUES, KC_LPRN, KC_RPRN, KC_COLN, KC_PIPE,    KC_NO, KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL, KC_NO,
                             //-------------------------------------------------//--------------------------------------------------------------//
                             KC_NO, KC_AT, KC_LCBR, KC_RCBR, KC_DLR, KC_TILD,       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_ESC, KC_SPC, KC_TAB,                                KC_NO, KC_NO, KC_NO, 
                             //-------------------------------------------------//-----------------------------------------------------------//
                             QK_CAPS_WORD_TOGGLE, KC_NO,                            KC_NO, KC_NO),
 
     // 6 - Function layer
     [6] = LAYOUT_split_4x6_5(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_F7, KC_F8, KC_F9, KC_F12, KC_NO,             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_F4, KC_F5, KC_F6, KC_F11, KC_NO,            KC_NO, KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_F1, KC_F2, KC_F3, KC_F10, KC_NO,          KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_ESC, KC_SPC, KC_TAB,                                KC_NO, KC_NO, KC_NO, 
                             //-------------------------------------------------//-----------------------------------------------------------//
                             QK_CAPS_WORD_TOGGLE, KC_NO,                            KC_NO, KC_NO),
 
     // 7 - One Handed layer (for mouse use)
     [7] = LAYOUT_split_4x6_5(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                     TG(7), TG(7), TG(7), TG(7), TG(7), TG(7),
                             //------------------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_NO, LGUI(KC_A), LGUI(KC_Z), LGUI(LSFT(KC_Z)), KC_NO,  TG(7), TG(7), TG(7), TG(7), TG(7), TG(7),
                             //------------------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_NO,              TG(7), TG(7), TG(7), TG(7), TG(7), TG(7),
                             //------------------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_NO, LGUI(KC_X), LGUI(KC_C), KC_NO, LGUI(KC_V),        TG(7), TG(7), TG(7), TG(7), TG(7), TG(7),
                             //------------------------------------------------------------//-----------------------------------------------------------//
                             //------------------------------------------------------------//-----------------------------------------------------------//
                             KC_BSPC, KC_SPC, KC_TAB,                                       TG(7), TG(7), TG(7),
                             //------------------------------------------------------------//-----------------------------------------------------------//
                             QK_CAPS_WORD_TOGGLE, KC_NO,                                    TG(7), TG(7)),
 };

// Define combos for bootloader and EEPROM reset
enum combo_events {
  COMBO_BOOTLOADER,
  COMBO_EE_RESET,
  COMBO_COUNT
};

const uint16_t PROGMEM bootloader_combo[] = {BOOT_L, BOOT_R, COMBO_END};
const uint16_t PROGMEM ee_reset_combo[] = {EE_RST_L, EE_RST_R, COMBO_END};

combo_t key_combos[] = {
  [COMBO_BOOTLOADER] = COMBO(bootloader_combo, QK_BOOT),
  [COMBO_EE_RESET] = COMBO(ee_reset_combo, QK_CLEAR_EEPROM),
};

// Handle the custom keycodes (they do nothing on their own)
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case BOOT_L:
        case BOOT_R:
        case EE_RST_L:
        case EE_RST_R:
            // These keys do nothing on their own
            return false;
        default:
            return true;
    }
}
 