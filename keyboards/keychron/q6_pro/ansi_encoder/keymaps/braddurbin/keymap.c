/* Copyright 2023 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include <stdio.h>
#include <pthread.h>

#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif

// clang-format off
enum layers{
  MAC_BASE,
  MAC_FN,
  WIN_BASE,
  GAMING,
  WIN_FN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_109_ansi(
        KC_ESC,   KC_F1,     KC_F2,     KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_F11,      KC_F12,     KC_MUTE,  KC_SNAP,  KC_SIRI,  RGB_TOG,  TO(MAC_BASE),  TO(WIN_BASE),  TO(GAMING),  _______,
        KC_GRV,   KC_1,      KC_2,      KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,      KC_MINS,     KC_EQL,     KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP,  KC_NUM,        KC_PSLS,       KC_PAST,     KC_PMNS,
        KC_TAB,   KC_Q,      KC_W,      KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,      KC_LBRC,     KC_RBRC,    KC_BSLS,  KC_DEL,   KC_END,   KC_PGDN,  KC_P7,         KC_P8,         KC_P9,       KC_PPLS,
        KC_F19,   KC_A,      KC_S,      KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,   KC_QUOT,                 KC_ENT,                                 KC_P4,         KC_P5,         KC_P6,
        KC_LSFT,             KC_Z,      KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,    KC_SLSH,                 KC_RSFT,            KC_UP,              KC_P1,         KC_P2,         KC_P3,       KC_PENT,
        KC_LCTL,  KC_LOPTN,  KC_LCMMD,                                KC_SPC,                                 KC_RCMMD,  MO(MAC_FN),  S(KC_F10),  KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_P0,                        KC_PDOT            ),
    [MAC_FN] = LAYOUT_109_ansi(
        _______,  KC_BRID,   KC_BRIU,   _______,  _______,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,   KC_VOLD,     KC_VOLU,    _______,  _______,  _______,  _______,  _______,       _______,       _______,     _______,
        _______,  BT_HST1,   BT_HST2,   BT_HST3,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,     _______,    _______,  _______,  _______,  _______,  _______,       _______,       _______,     _______,
        _______,  _______,   _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,     _______,    _______,  _______,  _______,  _______,  _______,       _______,       _______,     _______,
        KC_CAPS,  _______,   _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,                 _______,                                _______,       _______,       _______,
        _______,             _______,   _______,  _______,  _______,  BAT_LVL,  NK_TOGG,  _______,  _______,  _______,   _______,                 _______,            _______,            _______,       _______,       _______,     _______,
        _______,  _______,   _______,                                 _______,                                _______,   _______,     _______,    _______,  _______,  _______,  _______,  _______,                      _______            ),
    [WIN_BASE] = LAYOUT_109_ansi(
        KC_ESC,   KC_F1,     KC_F2,     KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_F11,      KC_F12,     KC_MUTE,  KC_PSCR,  KC_CTANA, RGB_TOG,  _______,       _______,       _______,     _______,
        KC_GRV,   KC_1,      KC_2,      KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,      KC_MINS,     KC_EQL,     KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP,  KC_NUM,        KC_PSLS,       KC_PAST,     KC_PMNS,
        KC_TAB,   KC_Q,      KC_W,      KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,      KC_LBRC,     KC_RBRC,    KC_BSLS,  KC_DEL,   KC_END,   KC_PGDN,  KC_P7,         KC_P8,         KC_P9,       KC_PPLS,
        KC_LWIN,  KC_A,      KC_S,      KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,   KC_QUOT,                 KC_ENT,                                 KC_P4,         KC_P5,         KC_P6,
        KC_LSFT,             KC_Z,      KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,    KC_SLSH,                 KC_RSFT,            KC_UP,              KC_P1,         KC_P2,         KC_P3,       KC_PENT,
        KC_LCTL,  KC_LALT,   KC_RCTL,                                 KC_SPC,                                 KC_RWIN,   MO(WIN_FN),  KC_APP,     KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_P0,                        KC_PDOT            ),
    [GAMING] = LAYOUT_109_ansi(
        KC_ESC,   KC_F1,     KC_F2,     KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_F11,      KC_F12,     KC_MUTE,  KC_PSCR,  KC_CTANA, RGB_TOG,  _______,       _______,       _______,     _______,
        KC_GRV,   KC_1,      KC_2,      KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,      KC_MINS,     KC_EQL,     KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP,  KC_NUM,        KC_PSLS,       KC_PAST,     KC_PMNS,
        KC_TAB,   KC_Q,      KC_W,      KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,      KC_LBRC,     KC_RBRC,    KC_BSLS,  KC_DEL,   KC_END,   KC_PGDN,  KC_P7,         KC_P8,         KC_P9,       KC_PPLS,
        KC_CAPS,  KC_A,      KC_S,      KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,   KC_QUOT,                 KC_ENT,                                 KC_P4,         KC_P5,         KC_P6,
        KC_LSFT,             KC_Z,      KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,    KC_SLSH,                 KC_RSFT,            KC_UP,              KC_P1,         KC_P2,         KC_P3,       KC_PENT,
        XXXXXXX,  KC_LALT,   KC_LCTL,                                 KC_SPC,                                 KC_RWIN,   MO(WIN_FN),  KC_APP,     KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_P0,                        KC_PDOT            ),
    [WIN_FN] = LAYOUT_109_ansi(
        _______,  KC_F14,    KC_F15,    _______,  _______,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,   KC_VOLD,     KC_VOLU,    _______,  _______,  _______,  _______,  _______,       _______,       _______,     _______,
        _______,  BT_HST1,   BT_HST2,   BT_HST3,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,     _______,    _______,  _______,  _______,  _______,  _______,       _______,       _______,     _______,
        _______,  _______,   _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,     _______,    _______,  _______,  _______,  _______,  _______,       _______,       _______,     _______,
        KC_CAPS,  _______,   _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,                 _______,                                _______,       _______,       _______,
        _______,             _______,   _______,  _______,  _______,  BAT_LVL,  NK_TOGG,  _______,  _______,  _______,   _______,                 _______,            _______,            _______,       _______,       _______,     _______,
        _______,  _______,   _______,                                 _______,                                _______,   _______,     _______,    _______,  _______,  _______,  _______,  _______,                      _______            ),
};

static bool alt_tab_sent = false;
static bool left_alt_active = false;
static bool left_ctrl_active = false;
static bool left_shift_active = false;
static bool q_macro_active = false;
static bool right_ctrl_active = false;
static bool win_app_quit = false;
static bool win_cursor_bottom = false;
static bool win_cursor_end = false;
static bool win_cursor_home = false;
static bool win_cursor_top = false;
static bool win_cursor_word_left = false;
static bool win_cursor_word_right = false;
static bool win_delete_file = false;
static bool win_delete_word_left = false;
static bool win_delete_word_right = false;
static bool win_find_replace_text = false;
static bool win_next_tab = false;
static bool win_previous_tab = false;
static bool win_scroll_line_down = false;
static bool win_scroll_line_up = false;
static bool win_scroll_page_down = false;
static bool win_scroll_page_up = false;
static bool win_smart_select_expand = false;
static bool win_smart_select_shrink = false;
static bool win_tab_move_left = false;
static bool win_tab_move_right = false;
static uint16_t key_timer;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    #ifdef CONSOLE_ENABLE
        uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    #endif

    if (layer_state_is(WIN_BASE)) {
        switch (keycode) {
            case KC_RCTL:
                if (record->event.pressed) {
                    right_ctrl_active = true;
                    alt_tab_sent = false;
                } else {
                    right_ctrl_active = false;
                    if (alt_tab_sent) {
                        unregister_code(KC_LALT);
                        alt_tab_sent = false;
                    }
                }
                break;
            case KC_LCTL:
                if (record->event.pressed) {
                    left_ctrl_active = true;
                } else {
                    left_ctrl_active = false;
                }
                break;
            case KC_LALT:
                if (record->event.pressed) {
                    left_alt_active = true;
                } else {
                    left_alt_active = false;
                }
                break;
            case KC_LSFT:
                if (record->event.pressed) {
                    left_shift_active = true;
                } else {
                    left_shift_active = false;
                }
                break;
            case KC_TAB:
                if (right_ctrl_active && !left_ctrl_active && !left_alt_active && record->event.pressed) {
                    unregister_code(KC_RCTL);
                    register_code(KC_LALT);
                    alt_tab_sent = true;
                }
                break;
            case KC_Q:
                if (record->event.pressed && right_ctrl_active && !left_ctrl_active && !left_alt_active && !left_shift_active) {
                    win_app_quit = true;
                    unregister_code(KC_RCTL);
                    register_code(KC_LALT);
                    register_code(KC_F4);
                    return false;
                } else if (!record->event.pressed && win_app_quit) {
                    win_app_quit = false;
                    unregister_code(KC_LALT);
                    unregister_code(KC_F4);
                    return false;
                }
                break;
            case KC_UP:
                if (record->event.pressed && right_ctrl_active && !left_ctrl_active && !left_alt_active) {
                    win_cursor_top = true;
                    register_code(KC_HOME);
                    return false;
                } else if (!record->event.pressed && win_cursor_top) {
                    win_cursor_top = false;
                    unregister_code(KC_HOME);
                    return false;
                }
                break;
            case KC_DOWN:
                if (record->event.pressed && right_ctrl_active && !left_ctrl_active && !left_alt_active) {
                    win_cursor_bottom = true;
                    register_code(KC_END);
                    return false;
                } else if (!record->event.pressed && win_cursor_bottom) {
                    win_cursor_bottom = false;
                    unregister_code(KC_END);
                    return false;
                }
                break;
            case KC_LEFT:
                if (!alt_tab_sent) {
                    if (record->event.pressed && right_ctrl_active && !left_ctrl_active && !left_alt_active) {
                        win_cursor_home = true;
                        unregister_code(KC_RCTL);
                        register_code(KC_HOME);
                        return false;
                    } else if (!record->event.pressed && win_cursor_home) {
                        win_cursor_home = false;
                        unregister_code(KC_HOME);
                        return false;
                    } else if (record->event.pressed && right_ctrl_active && !left_ctrl_active && left_alt_active && !left_shift_active) {
                        win_previous_tab = true;
                        unregister_code(KC_LALT);
                        register_code(KC_PGUP);
                        return false;
                    } else if (!record->event.pressed && win_previous_tab) {
                        win_previous_tab = false;
                        unregister_code(KC_PGUP);
                        return false;
                    } else if (record->event.pressed && right_ctrl_active && left_ctrl_active && left_alt_active && !left_shift_active) {
                        win_tab_move_left = true;
                        unregister_code(KC_RCTL);
                        unregister_code(KC_LALT);
                        register_code(KC_LSFT);
                        register_code(KC_PGUP);
                        return false;
                    } else if (!record->event.pressed && win_tab_move_left) {
                        win_tab_move_left = false;
                        unregister_code(KC_LSFT);
                        unregister_code(KC_PGUP);
                        return false;
                    } else if (record->event.pressed && !right_ctrl_active && !left_ctrl_active && left_alt_active) {
                        win_cursor_word_left = true;
                        register_code(KC_LCTL);
                        unregister_code(KC_LALT);
                    } else if (!record->event.pressed && win_cursor_word_left) {
                        win_cursor_word_left = false;
                        unregister_code(KC_LCTL);
                    } else if (record->event.pressed && !right_ctrl_active && left_ctrl_active && !left_alt_active && left_shift_active) {
                        win_smart_select_shrink = true;
                        unregister_code(KC_LCTL);
                        register_code(KC_LALT);
                    } else if (!record->event.pressed && win_smart_select_shrink) {
                        win_smart_select_shrink = false;
                        unregister_code(KC_LALT);
                    }
                }
                break;
            case KC_RIGHT:
                if (!alt_tab_sent) {
                    if (record->event.pressed && right_ctrl_active && !left_ctrl_active && !left_alt_active) {
                        win_cursor_end = true;
                        unregister_code(KC_RCTL);
                        register_code(KC_END);
                        return false;
                    } else if (!record->event.pressed && win_cursor_end) {
                        win_cursor_end = false;
                        unregister_code(KC_END);
                        return false;
                    } else if (record->event.pressed && right_ctrl_active && !left_ctrl_active && left_alt_active && !left_shift_active) {
                        win_next_tab = true;
                        unregister_code(KC_LALT);
                        register_code(KC_PGDN);
                        return false;
                    } else if (!record->event.pressed && win_next_tab) {
                        win_next_tab = false;
                        unregister_code(KC_PGDN);
                        return false;
                    } else if (record->event.pressed && right_ctrl_active && left_ctrl_active && left_alt_active && !left_shift_active) {
                        win_tab_move_right = true;
                        unregister_code(KC_RCTL);
                        unregister_code(KC_LALT);
                        register_code(KC_LSFT);
                        register_code(KC_PGDN);
                        return false;
                    } else if (!record->event.pressed && win_tab_move_right) {
                        win_tab_move_right = false;
                        unregister_code(KC_LSFT);
                        unregister_code(KC_PGDN);
                        return false;
                    } else if (record->event.pressed && !right_ctrl_active && !left_ctrl_active && left_alt_active) {
                        win_cursor_word_right = true;
                        register_code(KC_LCTL);
                        unregister_code(KC_LALT);
                    } else if (!record->event.pressed && win_cursor_word_right) {
                        win_cursor_word_right = false;
                        unregister_code(KC_LCTL);
                    } else if (record->event.pressed && !right_ctrl_active && left_ctrl_active && !left_alt_active && left_shift_active) {
                        win_smart_select_expand = true;
                        unregister_code(KC_LCTL);
                        register_code(KC_LALT);
                    } else if (!record->event.pressed && win_smart_select_expand) {
                        win_smart_select_expand = false;
                        unregister_code(KC_LALT);
                    }
                }
                break;
            case KC_PGUP:
                if (record->event.pressed && !right_ctrl_active && left_ctrl_active && !left_alt_active && !left_shift_active) {
                    win_scroll_line_up = true;
                    register_code(KC_UP);
                    return false;
                } else if (!record->event.pressed && win_scroll_line_up) {
                    win_scroll_line_up = false;
                    unregister_code(KC_UP);
                    return false;
                } else if (record->event.pressed && right_ctrl_active && !left_ctrl_active && !left_alt_active && !left_shift_active) {
                    win_scroll_page_up = true;
                    unregister_code(KC_RCTL);
                    register_code(KC_LALT);
                } else if (!record->event.pressed && win_scroll_page_up) {
                    win_scroll_page_up = false;
                    unregister_code(KC_LALT);
                }
                break;
            case KC_PGDN:
                if (record->event.pressed && !right_ctrl_active && left_ctrl_active && !left_alt_active && !left_shift_active) {
                    win_scroll_line_down = true;
                    register_code(KC_DOWN);
                    return false;
                } else if (!record->event.pressed && win_scroll_line_down) {
                    win_scroll_line_down = false;
                    unregister_code(KC_DOWN);
                    return false;
                } else if (record->event.pressed && right_ctrl_active && !left_ctrl_active && !left_alt_active && !left_shift_active) {
                    win_scroll_page_down = true;
                    unregister_code(KC_RCTL);
                    register_code(KC_LALT);
                } else if (!record->event.pressed && win_scroll_page_down) {
                    win_scroll_page_down = false;
                    unregister_code(KC_LALT);
                }
                break;
            case KC_BSPC:
                if (record->event.pressed && right_ctrl_active && !left_ctrl_active && !left_shift_active) {
                    win_delete_file = true;
                    unregister_code(KC_RCTL);
                    if (left_alt_active) {
                        unregister_code(KC_LALT);
                        register_code(KC_LSFT);
                    }
                    register_code(KC_DEL);
                    return false;
                } else if (!record->event.pressed && win_delete_file) {
                    win_delete_file = false;
                    unregister_code(KC_DEL);
                    unregister_code(KC_LSFT);
                    return false;
                } else if (record->event.pressed && !right_ctrl_active && !left_ctrl_active && left_alt_active && !left_shift_active) {
                    win_delete_word_left = true;
                    unregister_code(KC_LALT);
                    register_code(KC_LCTL);
                } else if (!record->event.pressed && win_delete_word_left) {
                    win_delete_word_left = false;
                    unregister_code(KC_LCTL);
                }
                break;
            case KC_DEL:
                if (record->event.pressed && !right_ctrl_active && !left_ctrl_active && left_alt_active && !left_shift_active) {
                    win_delete_word_right = true;
                    unregister_code(KC_LALT);
                    register_code(KC_LCTL);
                } else if (!record->event.pressed && win_delete_word_right) {
                    win_delete_word_right = false;
                    unregister_code(KC_LCTL);
                }
                break;
            case KC_F:
                if (record->event.pressed && right_ctrl_active && !left_ctrl_active && left_alt_active && !left_shift_active) {
                    win_find_replace_text = true;
                    unregister_code(KC_LALT);
                    register_code(KC_H);
                    return false;
                } else if (!record->event.pressed && win_find_replace_text) {
                    win_find_replace_text = false;
                    unregister_code(KC_H);
                    return false;
                }
                break;
            default:
                break;;
        }
    } else if (layer_state_is(GAMING)) {
        switch (keycode) {
            case KC_Q:
                if (record->event.pressed) {
                    if (layer_state_is(WIN_FN)) {
                        q_macro_active = true;
                        key_timer = timer_read();
                    } else {
                        q_macro_active = false;
                    }
                }
                break;
        }
    }

    return true;
}

void matrix_scan_user(void) {
    if (q_macro_active) {
        if (timer_elapsed(key_timer) > 500 && timer_elapsed(key_timer) < 30000) {
            unregister_code(KC_Q);
        } else if (timer_elapsed(key_timer) >= 30000) {
            key_timer = timer_read();
            register_code(KC_Q);
        }
    }
}

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][1][2] = {
    [MAC_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [MAC_FN]   = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
    [WIN_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [GAMING]   = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [WIN_FN]   = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI) }
};
#endif // ENCODER_MAP_ENABLE
