#include QMK_KEYBOARD_H

enum layers {
  _BASE,
  _SYM,
  _MOUSE,
};

enum custom_keycodes {
    KC_PARENS = SAFE_RANGE, // ()
    KC_BRACES,              // {}
    KC_BRACKETS,            // []
    KC_QUOTES,              // ""
    KC_APOS,                 // ''
    KC_BACKTICKS,            // `
    KC_DOLLARBRACES,         // ${}
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case KC_PARENS:
                tap_code16(S(KC_9));  // (
                tap_code(KC_SPACE);
                tap_code(KC_SPACE);
                tap_code16(S(KC_0));  // )
                tap_code(KC_LEFT);
                tap_code(KC_LEFT);
                return false;

            case KC_BRACES:
                tap_code16(S(KC_LBRC));  // {
                tap_code(KC_SPACE);
                tap_code(KC_SPACE);
                tap_code16(S(KC_RBRC));  // }
                tap_code(KC_LEFT);
                tap_code(KC_LEFT);
                return false;

            case KC_BRACKETS:
                tap_code(KC_LBRC);  // [
                tap_code(KC_SPACE);
                tap_code(KC_SPACE);
                tap_code(KC_RBRC);  // ]
                tap_code(KC_LEFT);
                tap_code(KC_LEFT);
                return false;

            case KC_QUOTES:
                register_code16(S(KC_QUOTE));  // Presiona Shift+'
                unregister_code16(S(KC_QUOTE));
                tap_code(KC_SPACE);
                tap_code(KC_SPACE);
                register_code16(S(KC_QUOTE));  // Presiona Shift+'
                unregister_code16(S(KC_QUOTE));
                tap_code(KC_LEFT);
                tap_code(KC_LEFT);
                return false;

            case KC_APOS:
                register_code(KC_QUOTE);  // Presiona '
                unregister_code(KC_QUOTE);
                tap_code(KC_SPACE);
                tap_code(KC_SPACE);
                register_code(KC_QUOTE);  // Presiona '
                unregister_code(KC_QUOTE);
                tap_code(KC_LEFT);
                tap_code(KC_LEFT);
                return false;

            case KC_BACKTICKS:
                register_code(KC_GRAVE);  // Presiona `
                unregister_code(KC_GRAVE);
                tap_code(KC_SPACE);
                tap_code(KC_SPACE);
                register_code(KC_GRAVE);  // Presiona `
                unregister_code(KC_GRAVE);
                tap_code(KC_LEFT);
                tap_code(KC_LEFT);
                return false;

            case KC_DOLLARBRACES:
                tap_code16(S(KC_4));  // $
                tap_code16(S(KC_LBRC));  // {
                tap_code(KC_SPACE);
                tap_code(KC_SPACE);
                tap_code16(S(KC_RBRC));  // }
                tap_code(KC_LEFT);
                tap_code(KC_LEFT);
                return false;
        }
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 [_BASE] = LAYOUT(
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
  KC_LSFT,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_HOME, KC_END,
  KC_LCTL,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_ENT,  KC_ENT,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_MINS,  KC_SCLN,
  KC_LGUI, KC_LALT, MO(1), KC_SPC, KC_SPC, MO(2), KC_NO, KC_NO
),

[_SYM] = LAYOUT(
  KC_TILD, KC_EXLM, KC_DQUO, KC_HASH, KC_DLR,  KC_PERC,                   KC_BSLS, KC_PSLS, KC_QUES, KC_SCLN, KC_EQUAL, KC_PMNS,
  KC_PIPE, KC_AT,   KC_CIRC, KC_AMPR, KC_ASTR, KC_QUOT,                   KC_LPRN, KC_RPRN, KC_P7,   KC_P8,   KC_P9,    KC_PPLS,
  KC_LSFT, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, KC_NO,                     KC_LBRC, KC_RBRC, KC_P4,   KC_P5,   KC_P6,    KC_PAST,
  KC_LSFT,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,   KC_SCLN, KC_COLN, KC_P1,   KC_P2,   KC_PDOT,  KC_PCMM,
  KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,   KC_LT,   KC_GT,   KC_P0
),

[_MOUSE] = LAYOUT(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  KC_NO,   MS_WHLL, MS_UP,   MS_WHLR, MS_WHLU, KC_NO,                     KC_NO,   KC_NO,   KC_UP,   MS_ACL0, MS_ACL1, MS_ACL2,
  KC_NO,   MS_LEFT, MS_DOWN, MS_RGHT, MS_WHLD, KC_NO,                     KC_NO,   KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,   KC_NO,
  KC_PARENS,   KC_BRACES,   KC_BRACKETS,   KC_QUOTES,   KC_APOS,   KC_BACKTICKS,   KC_DOLLARBRACES, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  KC_NO, KC_NO, KC_NO,   MS_BTN1, MS_BTN2,   KC_NO,   KC_NO,   KC_NO
)
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =  { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),      ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [1] =  { ENCODER_CCW_CW(KC_TRNS, KC_TRNS),      ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
    [2] =  { ENCODER_CCW_CW(KC_TRNS, KC_TRNS),      ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
};
#endif
