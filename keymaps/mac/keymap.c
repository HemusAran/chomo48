#include "chomo48.h"
#include "keymap_jp.h"

#ifdef CONSOLE_ENABLE
  #include <print.h>
#endif

enum layer_number {
    _BASE = 0,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum custom_keycodes {
    C_LOWER = SAFE_RANGE,
    C_RAISE,
    C_ENT,
};

#define D_EISU KC_LANG2   // Mac Eisu Key (or Windows 20H2 Eisu)
#define D_KANA KC_LANG1   // Mac Kana Key (or Windows 20H2 Kana)

#define D_UNDER LSFT(JP_BSLS)       // under bar
#define D_HOME LGUI(KC_LEFT)
#define D_END LGUI(KC_RIGHT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT(
    //,-----------------------------------------------------------------------------------------------------------.
         KC_TAB,    JP_Q,    JP_W,    JP_E,    JP_R,    JP_T,    JP_Y,    JP_U,    JP_I,    JP_O,    JP_P, JP_MINS,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        KC_LGUI,    JP_A,    JP_S,    JP_D,    JP_F,    JP_G,    JP_H,    JP_J,    JP_K,    JP_L, JP_SCLN, JP_COLN,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        KC_LSFT,    JP_Z,    JP_X,    JP_C,    JP_V,    JP_B,    JP_N,    JP_M, JP_COMM,  JP_DOT, JP_SLSH, D_UNDER,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        XXXXXXX, XXXXXXX, KC_LALT, KC_LGUI, C_LOWER,  KC_SPC,   C_ENT, C_RAISE, KC_LCTL, XXXXXXX, XXXXXXX,   RESET
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    ),

    [_LOWER] = LAYOUT(
    //,-----------------------------------------------------------------------------------------------------------.
         KC_ESC,    JP_1,    JP_2,    JP_3,    JP_4,    JP_5,    JP_6,    JP_7,    JP_8,    JP_9,    JP_0, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        KC_LGUI, KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, KC_BSPC, KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, XXXXXXX, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
        KC_LSFT,    JP_N, XXXXXXX, XXXXXXX,  KC_ENT,  KC_DEL,  D_HOME, KC_PGDN, KC_PGUP,   D_END, JP_SLSH, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        XXXXXXX, XXXXXXX, KC_LALT, KC_LGUI, _______, C_RAISE,   C_ENT, C_RAISE, KC_LCTL, XXXXXXX, XXXXXXX,   RESET
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    ),

    [_RAISE] = LAYOUT(
    //,-----------------------------------------------------------------------------------------------------------.
         KC_ESC, JP_EXLM, JP_DQUO, JP_HASH,  JP_DLR, JP_PERC, JP_AMPR, JP_QUOT, JP_LPRN, JP_RPRN, JP_CIRC,  JP_EQL,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        KC_LGUI, XXXXXXX,    JP_S, KC_JYEN, JP_PIPE, JP_LBRC, JP_RBRC,  JP_GRV, JP_TILD,   JP_AT, JP_PLUS, JP_ASTR,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, JP_LCBR, JP_RCBR, JP_BSLS, JP_LABK, JP_RABK, JP_QUES, JP_UNDS,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        XXXXXXX, XXXXXXX, KC_LALT, KC_LGUI, C_LOWER, _______,   C_ENT, _______, KC_LCTL, XXXXXXX, XXXXXXX,   RESET
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    ),

    [_ADJUST] = LAYOUT(
    //,-----------------------------------------------------------------------------------------------------------.
        JP_ZKHK,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   RESET, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        KC_LGUI,   KC_F5,   KC_F6,   KC_F7,   KC_F8, KC_BTN1, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, XXXXXXX, KC_CAPS,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        KC_LSFT,   KC_F9,  KC_F10,  KC_F11,  KC_F12, KC_BTN2, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_INT2,  KC_APP,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        XXXXXXX, XXXXXXX, KC_LALT, KC_LGUI, _______, _______,   C_ENT, _______, KC_LCTL, XXXXXXX, XXXXXXX,   RESET
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    )
};

// キーを単押しとして処理するかを判定するための変数。経過時間次第では単押しとして処理しない。
static bool lower_pressed = false;
static uint16_t lower_pressed_time = 0;
static bool raise_pressed = false;
static uint16_t raise_pressed_time = 0; 
static bool enter_pressed = false;
static uint16_t enter_pressed_time = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    //uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif

    switch (keycode) {
        case C_LOWER:
            if (record->event.pressed) {
                lower_pressed = true;
                lower_pressed_time = record->event.time;
                
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);

                if (lower_pressed && (TIMER_DIFF_16(record->event.time, lower_pressed_time) < TAPPING_TERM_CUSTOM)) {
                    // 単押しとして処理する
                    register_code(D_EISU);
                    unregister_code(D_EISU);
                } else {
                    // 時間が経過したため単押しとして処理しない
                }
                lower_pressed = false;
            }
            return false;
            break;

        case C_RAISE:
            if (record->event.pressed) {
                raise_pressed = true;
                raise_pressed_time = record->event.time;

                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);

                if (raise_pressed && (TIMER_DIFF_16(record->event.time, raise_pressed_time) < TAPPING_TERM_CUSTOM)) {
                    // 単押しとして処理する
                    register_code(D_KANA);
                    unregister_code(D_KANA);
                } else {
                    // 時間が経過したため単押しとして処理しない
                }
                raise_pressed = false;
            }
            return false;
            break;

        case C_ENT:
            if (record->event.pressed) {
                enter_pressed = true;
                enter_pressed_time = record->event.time;

                register_code(KC_RSFT);
            } else {
                unregister_code(KC_RSFT);

                if (enter_pressed && (TIMER_DIFF_16(record->event.time, enter_pressed_time) < TAPPING_TERM_CUSTOM)) {
                    // 単押しとして処理する
                    register_code(KC_ENT);
                    unregister_code(KC_ENT);
                } else {
                    // 時間が経過したため単押しとして処理しない
                }
                enter_pressed = false;
            }
            return false;
            break;

        default:
            if (record->event.pressed) {
                // 別のキーが押された場合、単押しではないためフラグを寝かせる。
                lower_pressed = false;
                raise_pressed = false;
                enter_pressed = false;
            }
            break;
    }

    return true;
}

#ifdef CONSOLE_ENABLE
void matrix_init_kb(void) {
    debug_enable = true;
    debug_matrix = true;
    debug_mouse  = true;
}
#endif
