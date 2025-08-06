#include QMK_KEYBOARD_H

static void handleBoot(void);
static uint32_t key_timer_boot = 0;
uint32_t tiempo_boot = 0;
bool is_boot_active = false;
bool override_rgb = false;

typedef struct {
  bool is_press_action;
  int state;
} tap;

enum layers {
  _BASE,
  _SYM,
  _MOUSE,
};
enum custom_keycodes {
    KC_DOLLARBRACES = SAFE_RANGE,
    ONOFFBOT
};

enum {
  ALT_OSL1 = 0,
  TD_ENE
};

#define SINGLE_TAP     1
#define SINGLE_HOLD    2
#define DOUBLE_TAP     3
#define DOUBLE_HOLD    4
#define TRIPLE_TAP     5
#define TRIPLE_HOLD    6

int cur_dance (tap_dance_state_t *state);
void alt_finished (tap_dance_state_t *state, void *user_data);
void alt_reset (tap_dance_state_t *state, void *user_data);

void handleBoot(){
  is_boot_active = !is_boot_active;
  if(is_boot_active){
    override_rgb = true;
    rgblight_mode_noeeprom(RGB_MATRIX_CYCLE_LEFT_RIGHT);
    tiempo_boot = 60000; //1 minuto
  }else{
    override_rgb = false;
    tiempo_boot = 0;
  }  
}

layer_state_t layer_state_set_user(layer_state_t state) {
  if (override_rgb) return state;  
  switch (get_highest_layer(state)) {
    case _BASE:
        rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
        rgb_matrix_sethsv(170, 255, 255); // Azul
        break;
    case _SYM:
        rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
        rgb_matrix_sethsv(85, 255, 255); // Verde
        break;
    case _MOUSE:
        rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
        rgb_matrix_sethsv(0, 255, 255); // Rojo
        break;
  }
  return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case KC_DOLLARBRACES:
              tap_code16(S(KC_4));  // $
              tap_code16(S(KC_LBRC));  // {
              tap_code16(S(KC_RBRC));  // }
              return false;
            case ONOFFBOT:
              if (record->event.pressed){
                handleBoot();
              }
              return false;
            case KC_NO:
              if (is_oneshot_layer_active()){
                clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
              }
              return true;
            default:
              return true;
        }
    }
    return true;
}

void matrix_scan_user(void) {
  if (timer_elapsed32(key_timer_boot) > tiempo_boot) {
      key_timer_boot = timer_read32();
      if(is_boot_active){
        tap_code(KC_2);
      }
    } 
}

int cur_dance (tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->pressed) return SINGLE_HOLD;
    else return SINGLE_TAP;
  }
  else if (state->count == 2) {
    if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  else if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8;
}

static tap alttap_state = {
  .is_press_action = true,
  .state = 0
};

void alt_finished (tap_dance_state_t *state, void *user_data) {
  alttap_state.state = cur_dance(state);
  switch (alttap_state.state) {
    case SINGLE_TAP: 
      set_oneshot_layer(_MOUSE, ONESHOT_START); 
      clear_oneshot_layer_state(ONESHOT_PRESSED);
      break;
    case SINGLE_HOLD: 
      register_code(KC_LALT); 
      break;
    case DOUBLE_TAP:
      set_oneshot_layer(_MOUSE, ONESHOT_START); 
      set_oneshot_layer(_MOUSE, ONESHOT_PRESSED);
      break;
    case DOUBLE_HOLD: 
      register_code(KC_LALT); 
      layer_on(_MOUSE); 
      break;
  }
}
void alt_reset (tap_dance_state_t *state, void *user_data) {
  switch (alttap_state.state) {
    case SINGLE_TAP: 
      break;
    case SINGLE_HOLD: 
      unregister_code(KC_LALT); 
      break;
    case DOUBLE_TAP: 
      break;
    case DOUBLE_HOLD: 
      layer_off(_MOUSE); 
      unregister_code(KC_LALT); 
      break;
  }
  alttap_state.state = 0;
}

void dance_cln_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(KC_N);
    } else {
        SEND_STRING(SS_DOWN(X_RALT) SS_TAP(X_N));
        clear_keyboard();
    }
}

void dance_cln_reset(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(KC_N);
    }
}

tap_dance_action_t tap_dance_actions[] = {
  [ALT_OSL1]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL,alt_finished, alt_reset),
  [TD_ENE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_cln_finished, dance_cln_reset)
};  


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 [_BASE] = LAYOUT(
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
  KC_LSFT,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_HOME, KC_END,
  KC_LCTL,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_ENT,  KC_ENT,  TD(TD_ENE),    KC_M,    KC_COMM, KC_DOT,  KC_MINS,  KC_SCLN,
  KC_LGUI, TD(ALT_OSL1), MO(1), KC_SPC, KC_SPC, MO(2), KC_NO, KC_NO
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
  KC_NO,   KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO,                     KC_NO,   KC_NO,   KC_UP,   KC_NO, KC_NO, KC_NO,
  KC_LSFT,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                     KC_NO,   KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,   KC_NO,
  KC_LCTL,   KC_DOLLARBRACES,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  KC_NO, TD(ALT_OSL1), KC_NO,   KC_NO, KC_NO,   KC_NO,   KC_NO,   ONOFFBOT
)
};