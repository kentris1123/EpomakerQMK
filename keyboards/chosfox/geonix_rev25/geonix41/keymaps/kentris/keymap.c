#include QMK_KEYBOARD_H
#include "rdmctmzt_common.h"

enum layers {
    _BASE_MAC,
    _BASE_WIN,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum custom_keycodes {
    ALT_TAB = SAFE_RANGE,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define KENTRIS_LAYOUT(...) LAYOUT_tkl_ansi(__VA_ARGS__)

#define KENTRIS_BASE \
    KC_GRV,          KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, \
    LCTL_T(KC_RBRC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, RCTL_T(KC_QUOT), \
    LSFT_T(KC_MINS), KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_EQL), \
    KC_F13,          KC_F14,  KC_LGUI, KC_LALT, KC_SPC,  RAISE,   RAISE,   LOWER,   KC_RALT, KC_RGUI, KC_F15,  KC_F16

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base
     * ,-----------------------------------------------------------------------------------.
     * |   `  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |   [  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | ]/Ctl|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  | '/Ctl|
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | -/Sft|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | =/Sft|
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |  F13 |  F14 | GUI  | Alt  |Space |Raise |Raise |Lower | RAlt | RGUI |  F15 |  F16 |
     * `-----------------------------------------------------------------------------------'
     *
     * The Geonix firmware persists a Mac/Windows selection by enabling either
     * layer 0 or 1. Keep both layers identical so that selection cannot replace
     * the Kentris base layout.
     */
    [_BASE_MAC] = KENTRIS_LAYOUT(KENTRIS_BASE),
    [_BASE_WIN] = KENTRIS_LAYOUT(KENTRIS_BASE),

    /* Lower: function keys, numbers, and shifted numbers. */
    [_LOWER] = LAYOUT_tkl_ansi(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        KC_PIPE, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
        _______, S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5), S(KC_6), S(KC_7), S(KC_8), S(KC_9), S(KC_0), _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    /* Raise: navigation, editing, media controls, and Alt-Tab. */
    [_RAISE] = LAYOUT_tkl_ansi(
        _______, XXXXXXX, ALT_TAB, XXXXXXX, XXXXXXX, ALT_TAB, KC_PSCR, KC_SCRL, KC_PAUS, ALT_TAB, XXXXXXX, QK_BOOT,
        _______, KC_DEL,  KC_TAB,  KC_UP,   KC_BSPC, KC_ENT,  KC_INS,  KC_HOME, KC_PGUP, KC_VOLD, KC_VOLU, KC_MUTE,
        _______, KC_LALT, KC_LEFT, KC_DOWN, KC_RGHT, KC_ESC,  KC_DEL,  KC_END,  KC_PGDN, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    /* Adjust: hold Lower + either Raise. Wireless controls follow the factory
     * Geonix order; battery and lighting controls remain available as well. */
    [_ADJUST] = LAYOUT_tkl_ansi(
        MD_USB,  MD_BLE1, MD_BLE2, MD_BLE3, MD_24G,  RM_NEXT, QK_BAT,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RM_TOGG,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RM_VALU, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, RM_SPDD, RM_VALD, RM_SPDU
    ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

/* geonix41.c owns process_record_user() for wireless/RGB handling. The core's
 * post-processing hook lets this keymap add the Planck Alt-Tab behavior without
 * replacing that board-level processing. */
void post_process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ALT_TAB:
            if (record->event.pressed) {
                register_code(KC_LALT);
                tap_code(KC_TAB);
            }
            break;

        case RAISE:
            // Keep Left Alt held for repeated Alt-Tab presses, then release it
            // when the Raise key is released.
            if (!record->event.pressed) {
                unregister_code(KC_LALT);
            }
            break;
    }
}
