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
 
 const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 
     // 0 - Alpha layer
     [0] = LAYOUT_split_4x6_5(KC_NO, KC_1, KC_2, KC_3, KC_4, KC_5,                  KC_6, KC_7, KC_8, KC_9, KC_0, KC_NO,
                              //-------------------------------------------------//-----------------------------------------------------------//
                              KC_NO, KC_Q, KC_W, KC_F, KC_P, KC_B,                  KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_NO,
                              //-------------------------------------------------//-----------------------------------------------------------//
                              KC_NO, HOME_A, HOME_R, HOME_S, HOME_T, KC_G,          KC_M, HOME_N, HOME_E, HOME_I, HOME_O, KC_NO,
                              //-------------------------------------------------//-----------------------------------------------------------//
                              KC_NO, KC_Z, KC_X, KC_C, KC_D, KC_V,                  KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, KC_NO,
                              //-------------------------------------------------//-----------------------------------------------------------//
                              //-------------------------------------------------//-----------------------------------------------------------//
                              LT(1, KC_ESC), LT(2, KC_SPC), LT(3, KC_TAB),           LT(4, KC_ENT), LT(5, KC_BSPC), LT(6, KC_DEL), 
                              //-------------------------------------------------//-----------------------------------------------------------//
                              KC_NO, KC_NO,                                        KC_NO, KC_NO),
 
     // 1 - Nav layer
     [1] = LAYOUT_split_4x6_5(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,           KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,           KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_NO,   KC_NO, KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,           KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             //-------------------------------------------------//-----------------------------------------------------------//
                             LT(1, KC_ESC), LT(2, KC_SPC), LT(3, KC_TAB),           LT(4, KC_ENT), LT(5, KC_BSPC), LT(6, KC_DEL), 
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_NO,                                        KC_NO, KC_NO),
 
     // 2 - Mouse layer
     [2] = LAYOUT_split_4x6_5(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,           KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,           KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_NO,   KC_NO, KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,           KC_NO, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             //-------------------------------------------------//-----------------------------------------------------------//
                             LT(1, KC_ESC), LT(2, KC_SPC), LT(3, KC_TAB),           LT(4, KC_ENT), LT(5, KC_BSPC), LT(6, KC_DEL),  
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_NO,                                        KC_NO, KC_NO),
 
     // 3 - Button layer
     [3] = LAYOUT_split_4x6_5(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,           KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,           KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_NO,   KC_NO, KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,           KC_NO, KC_BTN1, KC_BTN2, KC_BTN3, KC_NO, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             //-------------------------------------------------//-----------------------------------------------------------//
                             LT(1, KC_ESC), LT(2, KC_SPC), LT(3, KC_TAB),           LT(4, KC_ENT), LT(5, KC_BSPC), LT(6, KC_DEL), 
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_NO,                                        KC_NO, KC_NO),
 
     // 4 - Media layer
     [4] = LAYOUT_split_4x6_5(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,           KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,           KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,           KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,           KC_NO, KC_VOLD, KC_VOLU, KC_MNXT, KC_MPLY, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             //-------------------------------------------------//-----------------------------------------------------------//
                             LT(1, KC_ESC), LT(2, KC_SPC), LT(3, KC_TAB),           LT(4, KC_ENT), LT(5, KC_BSPC), LT(6, KC_DEL), 
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_NO,                                        KC_NO, KC_NO),
 
     // 5 - Coding layer
     [5] = LAYOUT_split_4x6_5(KC_5, KC_1, KC_2, KC_3, KC_4, KC_5,                  KC_6, KC_7, KC_8, KC_9, KC_0, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_Q, KC_W, KC_F, KC_P, KC_B,                  KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, HOME_A, HOME_R, HOME_S, HOME_T, KC_G,          KC_M, HOME_N, HOME_E, HOME_I, HOME_O, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_Z, KC_X, KC_C, KC_D, KC_V,                  KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             //-------------------------------------------------//-----------------------------------------------------------//
                             LT(1, KC_ESC), LT(2, KC_SPC), LT(3, KC_TAB),           LT(4, KC_ENT), LT(5, KC_BSPC), LT(6, KC_DEL), 
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_NO,                                        KC_NO, KC_NO),
 
     // 6 - Symbol layer
     [6] = LAYOUT_split_4x6_5(KC_6, KC_1, KC_2, KC_3, KC_4, KC_5,                  KC_6, KC_7, KC_8, KC_9, KC_0, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_Q, KC_W, KC_F, KC_P, KC_B,                  KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, HOME_A, HOME_R, HOME_S, HOME_T, KC_G,          KC_M, HOME_N, HOME_E, HOME_I, HOME_O, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_Z, KC_X, KC_C, KC_D, KC_V,                  KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, KC_NO,
                             //-------------------------------------------------//-----------------------------------------------------------//
                             //-------------------------------------------------//-----------------------------------------------------------//
                             LT(1, KC_ESC), LT(2, KC_SPC), LT(3, KC_TAB),           LT(4, KC_ENT), LT(5, KC_BSPC), LT(6, KC_DEL), 
                             //-------------------------------------------------//-----------------------------------------------------------//
                             KC_NO, KC_NO,                                        KC_NO, KC_NO),
 };
 