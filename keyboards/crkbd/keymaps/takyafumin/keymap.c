/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include <stdio.h>


enum custom_keycodes {
    MYC_CLN = SAFE_RANGE,
    MYS_QES,
    //MY_RAISE,
    //MY_LOWER,
};

enum custom_tapdance_keys {
    TD_ESCQ,
    TD_MINS,
    TD_BSLS,
    TD_GRV,
    TD_QUOT,
    TD_EQL,
    TD_LBRC,
    TD_RBRC,
    TD_COMM,
    TD_DOT,
};

// --------------------
// tap dance definitions
// --------------------
void td_lbrc_finished(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            SEND_STRING("(");
            break;
        case 2:
            SEND_STRING("[");
            break;
        case 3:
            SEND_STRING("{");
            break;
    }
};
void td_rbrc_finished(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            SEND_STRING(")");
            break;
        case 2:
            SEND_STRING("]");
            break;
        case 3:
            SEND_STRING("}");
            break;
    }
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_ESCQ]   = ACTION_TAP_DANCE_DOUBLE(KC_Q,    KC_ESC),
    [TD_MINS]   = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_UNDS),
    [TD_BSLS]   = ACTION_TAP_DANCE_DOUBLE(KC_PIPE, KC_BSLS),
    [TD_GRV]    = ACTION_TAP_DANCE_DOUBLE(KC_TILD, KC_GRV),
    [TD_QUOT]   = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_DQUO),
    [TD_EQL]    = ACTION_TAP_DANCE_DOUBLE(KC_EQL,  KC_PLUS),
    [TD_LBRC]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_lbrc_finished, NULL),
    [TD_RBRC]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_rbrc_finished, NULL),
    /* [TD_COMM]   = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_LT), */
    /* [TD_DOT]    = ACTION_TAP_DANCE_DOUBLE(KC_DOT,  KC_GT), */
};

// --------------------
// custom keyterms
// --------------------
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LCTL_T(KC_A):
      return TAPPING_TERM + 20;
    case RCTL_T(KC_SCLN):
      return TAPPING_TERM + 20;
    default:
      return TAPPING_TERM;
  }
}


// --------------------
// キーのalias
// --------------------
#define CTLSPC   LCTL_T(KC_SPC)
#define SFT_A    LSFT_T(KC_A)
#define SFT_SCN  LSFT_T(KC_SCLN)
#define SFT_F1   LSFT_T(KC_F1)
#define GUI_Z    LGUI_T(KC_Z)
#define ALT_SLSH LALT_T(KC_SLSH)
#define DD_Q     TD(TD_ESCQ)
#define DD_EQL   TD(TD_EQL)
#define DD_MINS  TD(TD_MINS)
#define DD_LBRC  TD(TD_LBRC)
#define DD_RBRC  TD(TD_RBRC)
#define DD_QUOT  TD(TD_QUOT)
#define DD_BSLS  TD(TD_BSLS)
#define DD_GRV   TD(TD_GRV)
#define SPC  KC_SPC
#define ESC  KC_ESC
#define L1   KC_LNG1
#define L2   KC_LNG2



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            _______,    DD_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, _______,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            _______,   SFT_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, SFT_SCN, _______,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            _______,   GUI_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT,ALT_SLSH, _______,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                               LT(3,L1),LT(1,L2),  CTLSPC,     KC_ENT,LT(2,ESC),KC_RALT
                                            //`--------------------------'  `--------------------------'
  ),

  [1] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,------------------------------------------------------
        //         ,     !  ,     @  ,     #  ,     $  ,    %   ,                    ,     ^  ,     &  ,     *  ,    \   ,     ~  ,
        //,------------------------------------------------------.                    ,-----------------------------------------------------.
        //         , LAYER3 ,        ,  HOME  ,   END  ,    ~   ,                    ,   ([{  ,    -   ,     =  ,   '"   ,     :  ,
        //,------------------------------------------------------.                    ,-----------------------------------------------------.
        //         ,  SHIFT ,        ,        ,        ,        ,                    ,   )]}  ,     \  ,     <  ,    >   ,     ?  ,
        //,------------------------------------------------------.                    ,-----------------------------------------------------.
            _______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_BSLS,  KC_GRV, _______,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            _______, KC_LSFT, XXXXXXX, KC_PGUP,  KC_ESC,  DD_GRV,                      DD_LBRC, KC_MINS,  KC_EQL, DD_QUOT, MYC_CLN, _______,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            _______, KC_LGUI, KC_HOME, KC_PGDN,  KC_END, _______,                      DD_RBRC, DD_BSLS,   KC_LT,   KC_GT, MYS_QES, _______,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                                KC_LCTL, _______, _______,    KC_BSPC, _______, _______
                                            //`--------------------------'  `--------------------------'
        ),

  [2] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, _______,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            _______,  SFT_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT,  KC_TAB, _______,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            _______,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,                       KC_F11,  KC_F12, _______, _______, _______, _______,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                                KC_PSCR, KC_RALT,  KC_DEL,    _______, _______, _______
                                            //`--------------------------'  `--------------------------'
  ),

  [3] = LAYOUT_split_3x6_3(
       //,-----------------------------------------------------.                    ,-----------------------------------------------------.
           _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX,    KC_7,    KC_8,    KC_9, XXXXXXX, _______,
       //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
           _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX,    KC_4,    KC_5,    KC_6,  KC_DEL, XXXXXXX,
       //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
           _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX,    KC_1,    KC_2,    KC_3, XXXXXXX, XXXXXXX,
       //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                               _______, _______, _______,    _______, _______,    KC_0
                                           //`--------------------------'  `--------------------------'
  )
};


#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case L_BASE:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case L_LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case L_RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case L_ADJUST:
        case L_ADJUST|L_LOWER:
        case L_ADJUST|L_RAISE:
        case L_ADJUST|L_LOWER|L_RAISE:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
    }
}


char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
    return false;
}

#endif // OLED_ENABLE


// --------------------
// layerキーを押しているか
// --------------------
static bool layer_switch_pressed = false;

/**
 * キーを押したときの処理
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
        //case MY_RAISE:
        //    if (record->event.pressed) {
        //        layer_switch_pressed = true;
        //        layer_on(1);
        //    } else {
        //        layer_off(1);
        //        if (layer_switch_pressed) {
        //            tap_code(KC_LNG2);
        //        }
        //        layer_switch_pressed = false;
        //    }
        //    break;

        //case MY_LOWER:
        //    if (record->event.pressed) {
        //        layer_switch_pressed = true;
        //        layer_on(2);
        //    } else {
        //        layer_off(2);
        //        if (layer_switch_pressed) {
        //            tap_code(KC_LNG1);
        //        }
        //        layer_switch_pressed = false;
        //    }
        //    break;

        case MYC_CLN:
            if (record->event.pressed) {
                register_mods(MOD_BIT(KC_LCTL));
            } else {
                unregister_mods(MOD_BIT(KC_LCTL));
                if (!record->tap.count) {
                    register_mods(MOD_MASK_SHIFT);
                    tap_code(KC_SCLN);
                    unregister_mods(MOD_MASK_SHIFT);
                }
            }
            layer_switch_pressed = false;
            break;

        case MYS_QES:
            if (record->event.pressed) {
                register_mods(MOD_BIT(KC_LSFT));
            } else {
                if (!record->tap.count) {
                    tap_code(KC_SLSH);
                }
                unregister_mods(MOD_BIT(KC_LSFT));
            }
            layer_switch_pressed = false;
            break;

        default:
            layer_switch_pressed = false;
            break;
    }

    set_keylog(keycode, record);
    return true;
}
