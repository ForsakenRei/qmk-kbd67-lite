/* Copyright 2019 dnsnrk
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

enum custom_keycodes
{
  TSK_MGR,
};

typedef enum
{ // quad function tap-dance
  TD_NONE,
  TD_UNKNOWN,
  TD_SINGLE_TAP,
  TD_SINGLE_HOLD,
  TD_DOUBLE_TAP
} td_state_t;

typedef struct
{
  bool is_press_action;
  td_state_t state;
} td_tap_t;

enum custom_tap_dance
{
  CAPS_LAYR,
};

// Declare the functions to be used with your tap dance key(s)

// Function associated with all tap dances
td_state_t cur_dance(qk_tap_dance_state_t *state);

// Functions associated with individual tap dances
void ql_finished(qk_tap_dance_state_t *state, void *user_data);
void ql_reset(qk_tap_dance_state_t *state, void *user_data);

#define CAP_LYR TD(CAPS_LAYR)
#define TSK_MGR C(S(KC_ESC))
#define OSK_ALT OSM(MOD_LALT) // one shot mods
#define OSK_SFT OSM(MOD_RSFT)

enum {
      _L0 = 0,
      _L1,
      _L2
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_L0] = LAYOUT_65_ansi_blocker( /* Base Layer */
                                       KC_ESC,  KC_1,     KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,   KC_HOME,
                                       KC_TAB,  KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLASH, KC_PGUP,
                                       CAP_LYR, KC_A,     KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,            KC_ENT,    KC_PGDN,
                                       KC_LSFT, KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,            KC_RSFT,  KC_UP,     KC_END,
                                       KC_LCTL, KC_LGUI,  KC_LALT,                   KC_SPC,                    TT(2),            KC_RCTL,            KC_LEFT,  KC_DOWN,   KC_RGHT),
    [_L1] = LAYOUT_65_ansi_blocker( /* FN, media*/
                                       KC_GRV,  KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,  KC_DEL,    KC_INS,
                                       _______, KC_HOME,  KC_UP,   KC_END,  KC_PGUP, _______, _______, _______, _______, _______, _______,  _______,  _______, KC_INS,    KC_PSCR,
                                       TO(0),   KC_LEFT,  KC_DOWN, KC_RGHT, KC_PGDN, _______, _______, _______, _______, _______, _______,  _______,           _______,   KC_END,
                                       _______, _______,  _______, KC_CALC, _______, _______, _______, TSK_MGR, _______, _______, _______,            KC_MUTE, KC_VOLU,   KC_MPLY,
                                       _______, TO(2),    _______,                   _______,                   _______,          _______,            _______, KC_VOLD,   _______),
    [_L2] = LAYOUT_65_ansi_blocker( /* Numpad, RGB */
                                       RGB_TOG, RGB_M_P,  _______, _______, NK_TOGG, _______, _______, KC_P7,   KC_P8,   KC_P9,   _______, KC_PMNS,   KC_PPLS, _______,   RGB_SAI,
                                       _______, _______,  _______, _______, _______, _______, _______, KC_P4,   KC_P5,   KC_P6,   _______, KC_PAST,   KC_PSLS, _______,   RGB_SAD,
                                       TO(0),   _______,  _______, _______, _______, _______, _______, KC_P1,   KC_P2,   KC_P3,   _______, _______,            _______,   RGB_HUI,
                                       _______, RESET,    EEP_RST, _______, _______, _______, _______, KC_P0,   KC_P0,   KC_PDOT, KC_NLCK,            _______, RGB_MOD,   RGB_HUD,
                                       _______, _______,  _______,                   _______,                   TO(0),            RESET,              RGB_VAD, RGB_RMOD,  RGB_VAI)
};

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max)
{
  switch (get_highest_layer(layer_state))
  {
  case _L1:
    {
      rgb_matrix_set_color(14, 0xaa, 0xcc, 0x11);
    }
    break;
  case _L2:
    {
      rgb_matrix_set_color(29, 0xff, 0x99, 0x00);
    }
    break;
  default:
    break;
  }
}


// Determine the current tap dance state
td_state_t cur_dance(qk_tap_dance_state_t *state)
{
  if (state->count == 1)
  {
    if (!state->pressed)
      return TD_SINGLE_TAP;
    else
      return TD_SINGLE_HOLD;
  }
  else if (state->count == 2)
    return TD_DOUBLE_TAP;
  else
    return TD_UNKNOWN;
}

// Initialize tap structure associated with example tap dance key
static td_tap_t ql_tap_state = {
    .is_press_action = true,
    .state = TD_NONE};

// Functions that control what our tap dance key does
void ql_finished(qk_tap_dance_state_t *state, void *user_data)
{
  ql_tap_state.state = cur_dance(state);
  switch (ql_tap_state.state)
  {
  case TD_SINGLE_TAP:
    tap_code(KC_CAPS);
    break;
  case TD_SINGLE_HOLD:
    layer_on(_L1);
    break;
  case TD_DOUBLE_TAP:
    // Check to see if the layer is already set
    if (layer_state_is(_L1))
    {
      // If already set, then switch it off
      layer_off(_L1);
    }
    else
    {
      // If not already set, then switch the layer on
      layer_on(_L1);
    }
    break;
  default:
    break;
  }
}

void ql_reset(qk_tap_dance_state_t *state, void *user_data)
{
  // If the key was held down and now is released then switch off the layer
  if (ql_tap_state.state == TD_SINGLE_HOLD)
  {
    layer_off(_L1);
  }
  ql_tap_state.state = TD_NONE;
}

// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    [CAPS_LAYR] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, ql_finished, ql_reset, 275)};

void keyboard_post_init_user(void)
{
  if (IS_HOST_LED_ON(USB_LED_NUM_LOCK))
  { // turn on Num lock by defautl
    tap_code(KC_NUMLOCK);
  }
}

const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPACE, KC_DELETE);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &delete_key_override,
    NULL // Null terminate the array of overrides!
};
