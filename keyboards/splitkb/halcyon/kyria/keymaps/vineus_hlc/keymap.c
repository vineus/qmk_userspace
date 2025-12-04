// Copyright 2024 splitkb.com (support@splitkb.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "timer.h"

enum layers {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST
};


// Aliases for readability
#define KC_CAPW LGUI(LSFT(KC_3))        // Capture whole screen
#define KC_CPYW LGUI(LSFT(LCTL(KC_3)))  // Copy whole screen
#define KC_CAPP LGUI(LSFT(KC_4))        // Capture portion of screen
#define KC_CPYP LGUI(LSFT(LCTL(KC_4)))  // Copy portion of screen
#define KC_RPYP LGUI(LSFT(KC_5))        // Record portion of screen
#define KC_1PWD LGUI(KC_BSLS)           // 1Password

#define KC_EMOJI LGUI(LCTL(KC_SPC))     // Emojis
#define KC_CLPB LGUI(LSFT(KC_V))        // Clipboard history
#define KC_HYPER LCTL(LALT(LGUI(LSFT(KC_NO))))         // Hyper key
#define KC_NOTIF LALT(KC_QUOT)
#define KC_LOCK LCTL(LGUI(KC_Q))        // Lock screen

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Esc   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  Bksp  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |Tab/Shft|   A  |   S  |  D   |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |  ' "   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LCtrl  |   Z  |   X  |   C  |   V  |   B  | Left | Right|  |  Up  | Down |   N  |   M  | ,  < | . >  | /  ? | Enter  |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | Hyper| GUI  | Alt  |Lower |Space |  | Space| Raise|  `   | Del  | Emoji|
 *                        |      |      |      |      |      |  |      |      | Alt  |      |/Hyper|
 *                        `----------------------------------'  `----------------------------------'
 */
    [_QWERTY] = LAYOUT_split_3x6_5_hlc(
      KC_ESC, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                                                  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
      MT(MOD_LSFT, KC_TAB) ,   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                                 KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, MT(MOD_LSFT, KC_QUOT),
      KC_LCTL,  KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_LEFT,   KC_RGHT,       KC_UP,  KC_DOWN, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
                           KC_HYPR, KC_LGUI, LOPT_T(KC_LSFT), LOWER, KC_SPC,       KC_SPC, RAISE, MT(MOD_RALT, KC_GRV),  KC_DEL, KC_EMOJI,
      KC_CPYP, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    ),
/*
 * Lower Layer: Symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |   ~    |  !   |  @   |  #   |  $   |  %   |                              |   ^  |  &   |  *   |  (   |   )  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              |      |   _  |  +   |  {   |   }  |   |    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |  Up  |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  | Left | Down |Right |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_LOWER] = LAYOUT_split_3x6_5_hlc(
      KC_GRV, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                                     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
      _______, _______, _______, _______, _______, _______,                                     _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
      _______, _______, _______, _______, KC_CLPB, _______, _______, _______,   _______,  KC_UP ,_______,_______,_______,_______,_______,_______,
                                 _______, _______, _______, _______, _______,   KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______,
      KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    ),
/*
    * Raise Layer: Number keys, media, navigation
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |   1  |  2   |  3   |  4   |  5   |                              |  6   |  7   |  8   |  9   |  0   |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              |      |   -  |   =  |   [  |   ]  |   \    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_RAISE] = LAYOUT_split_3x6_5_hlc(
      _______, KC_1, 	  KC_2,    KC_3,    KC_4,    KC_5,                                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, _______,
      _______, _______, _______, _______, _______, _______,                                     _______, KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,
      _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                               KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    ),
/*
 * Adjust Layer: Function keys, RGB
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        | F1   |  F2  | F3   | F4   | F5   |                              | F6   | F7   |  F8  | F9   | F10  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | TOG  | SAI  | HUI  | VAI  | MOD  |                              |      |      |      | F11  | F12  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      | SAD  | HUD  | VAD  | RMOD |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_ADJUST] = LAYOUT_split_3x6_5_hlc(
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
      _______, RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI, RGB_MOD,                                     _______, _______, _______, KC_F11,  KC_F12,  _______,
      _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD,_______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      KC_NO, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
    ),

// /*
//  * Halcyon Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  * ,-----------------------------------.                                              ,-----------------------------------.
//  * |      |      |       |      |      |                                              |      |      |       |      |      |
//  * `-----------------------------------'                                              `-----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT_split_3x6_5_hlc(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//
//       _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______
//     ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),  ENCODER_CCW_CW(KC_VOLD, KC_VOLU),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
    [1] = { ENCODER_CCW_CW(MS_WHLR, MS_WHLL),  ENCODER_CCW_CW(MS_WHLR, MS_WHLL),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
    [2] = { ENCODER_CCW_CW(MS_WHLD, MS_WHLU),  ENCODER_CCW_CW(MS_WHLD, MS_WHLU),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
    [3] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
};
#endif

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // Layer color indicators
    rgb_matrix_set_color(7, RGB_GREEN);
    rgb_matrix_set_color(38, RGB_RED);
    if (get_highest_layer(layer_state) > 0) {
        uint8_t layer = get_highest_layer(layer_state);

        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];

                if (index >= led_min && index < led_max && index != NO_LED &&
                keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
                    switch (layer) {
                        case 1:
                            rgb_matrix_set_color(index, RGB_GREEN);
                            break;
                        case 2:
                            rgb_matrix_set_color(index, RGB_RED);
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }

    // When HYPER key is pressed, set color to purple for keys C, V, I, S, P, W and L
    rgb_matrix_set_color(10, RGB_PURPLE);
    if ((get_mods() & MOD_MASK_CSAG) == (MOD_BIT(KC_LCTL)|MOD_BIT(KC_LSFT)|MOD_BIT(KC_LALT)|MOD_BIT(KC_LGUI))) {
        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];
                if (index >= led_min && index < led_max && index != NO_LED) {
                    if (keymap_key_to_keycode(0, (keypos_t){col,row}) == KC_C ||
                        keymap_key_to_keycode(0, (keypos_t){col,row}) == KC_V ||
                        keymap_key_to_keycode(0, (keypos_t){col,row}) == KC_I ||
                        keymap_key_to_keycode(0, (keypos_t){col,row}) == KC_S ||
                        keymap_key_to_keycode(0, (keypos_t){col,row}) == KC_P ||
                        keymap_key_to_keycode(0, (keypos_t){col,row}) == KC_W ||
                        keymap_key_to_keycode(0, (keypos_t){col,row}) == KC_R ||
                        keymap_key_to_keycode(0, (keypos_t){col,row}) == KC_L) {
                        rgb_matrix_set_color(index, RGB_PURPLE);
                    }
                }
            }
        }
    }

    // Emoji key
    rgb_matrix_set_color(41, RGB_PINK);

//    // Underglow breathing effect in gold
//    uint16_t now = timer_read();
//    uint8_t t = (now >> 5) & 0xFF;
//    uint8_t breath = t < 128 ? t * 2 : (255 - t) * 2;
//
//    for (uint8_t i = 0; i < 6; i++) {
//        if (i >= led_min && i < led_max) {
//            // Gold: R = breath, G = breath * 192 / 255, B = 0
//            rgb_matrix_set_color(i, breath, (breath * 192) / 255, 0);
//        }
//    }
//    for (uint8_t i = 31; i < 37; i++) {
//        if (i >= led_min && i < led_max) {
//            // Gold: R = breath, G = breath * 192 / 255, B = 0
//            rgb_matrix_set_color(i, breath, (breath * 192) / 255, 0);
//        }
//    }
    return false;
}

void keyboard_post_init_user(void) {
    rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE_WIDE);
    rgb_matrix_sethsv(HSV_GOLD);
    rgb_matrix_set_speed(64);
}
