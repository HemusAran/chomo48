#include "chomo48.h"
#include "keymap_jp.h"

enum layer_number {
    _BASE = 0,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum custom_keycodes {
    C_LOWER = SAFE_RANGE,
    C_RAISE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT(
    //,-----------------------------------------------------------------------------------------------------------.
         KC_TAB,    JP_Q,    JP_W,    JP_E,    JP_R,    JP_T,    JP_Y,    JP_U,    JP_I,    JP_O,    JP_P, JP_MINS,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        KC_LCTL,    JP_A,    JP_S,    JP_D,    JP_F,    JP_G,    JP_H,    JP_J,    JP_K,    JP_L, JP_SCLN, JP_COLN,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        KC_LSFT,    JP_Z,    JP_X,    JP_C,    JP_V,    JP_B,    JP_N,    JP_M, JP_COMM,  JP_DOT, JP_SLSH, JP_UNDS,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        XXXXXXX, XXXXXXX, KC_LGUI, KC_LALT, C_LOWER,  KC_SPC,  KC_ENT, C_RAISE, KC_LGUI, XXXXXXX, XXXXXXX,   RESET
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    ),

    [_LOWER] = LAYOUT(
    //,-----------------------------------------------------------------------------------------------------------.
         KC_ESC,    JP_1,    JP_2,    JP_3,    JP_4,    JP_5,    JP_6,    JP_7,    JP_8,    JP_9,    JP_0, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        KC_LCTL, KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, KC_BSPC, KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, XXXXXXX, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
        KC_LSFT,    JP_N, XXXXXXX, XXXXXXX,  KC_ENT,  KC_DEL, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, JP_SLSH, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        XXXXXXX, XXXXXXX, KC_LGUI, KC_LALT, _______,  KC_SPC,  KC_ENT, C_RAISE, KC_LGUI, XXXXXXX, XXXXXXX,   RESET
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    ),

    [_RAISE] = LAYOUT(
    //,-----------------------------------------------------------------------------------------------------------.
         KC_ESC, JP_EXLM, JP_DQUO, JP_HASH,  JP_DLR, JP_PERC, JP_AMPR, JP_QUOT, JP_LPRN, JP_RPRN, JP_CIRC,  JP_EQL,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        KC_LCTL, XXXXXXX,    JP_S, KC_JYEN, JP_PIPE, JP_LBRC, JP_RBRC,  JP_GRV, JP_TILD,   JP_AT, JP_PLUS, JP_ASTR,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, JP_LCBR, JP_RCBR, JP_BSLS, JP_LABK, JP_RABK, JP_QUES, JP_UNDS,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        XXXXXXX, XXXXXXX, KC_LGUI, KC_LALT, C_LOWER,  KC_SPC,  KC_ENT, _______, KC_LGUI, XXXXXXX, XXXXXXX,    RESET
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    ),

    [_ADJUST] = LAYOUT(
    //,-----------------------------------------------------------------------------------------------------------.
        JP_ZKHK,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   RESET, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR, XXXXXXX, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        KC_LCTL,   KC_F5,   KC_F6,   KC_F7,   KC_F8, KC_BTN1, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, XXXXXXX, JP_CAPS,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        KC_LSFT,   KC_F9,  KC_F10,  KC_F11,  KC_F12, KC_BTN2, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_INT2,  KC_APP,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        XXXXXXX, XXXXXXX, KC_LGUI, KC_LALT, _______,  KC_SPC,  KC_ENT, _______, KC_LGUI, XXXXXXX, XXXXXXX,   RESET
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
        case C_LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
            } else {
                layer_off(_LOWER);
            }
            return false;
            break;

        case C_RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
            } else {
                layer_off(_RAISE);
            }
            return false;
            break;

        default:
            break;
    }

    return true;
}