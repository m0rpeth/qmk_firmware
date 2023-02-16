#include QMK_KEYBOARD_H

//LEADER_EXTERNS();

enum layers {
    LYR_ALPHA = 0,
    LYR_RAISE,
    LYR_LOWER,
    LYR_NUMBLOCK,
    LYR_ADJUST,
};

enum custom_keycodes {
	KC_LWR = SAFE_RANGE,
	KC_RSE,
	KC_ADJUST
};

#define KC_NBL MO(LYR_NUMBLOCK)

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LT(0, KC_LWR):
        if (record->event.pressed) {
            // on hold
            layer_on(LYR_LOWER);
            update_tri_layer(LYR_LOWER, LYR_RAISE, LYR_ADJUST);
        } else {
            // on release
            layer_off(LYR_LOWER);
            update_tri_layer(LYR_LOWER, LYR_RAISE, LYR_ADJUST);
        }
        return false;
    case LT(0, KC_RSE):
        if (record->tap.count && record->event.pressed) {
            // on tap
            tap_code16(KC_ENT);
        } else if (record->event.pressed) {
            // on hold
            layer_on(LYR_RAISE);
            update_tri_layer(LYR_LOWER, LYR_RAISE, LYR_ADJUST);
        } else {
            // on release
            layer_off(LYR_RAISE);
            update_tri_layer(LYR_LOWER, LYR_RAISE, LYR_ADJUST);
        }
        return false;
    case LCTL_T(KC_EXLM):
        if (record->tap.count && record->event.pressed) {
            tap_code16(KC_EXLM); // Send KC_EXLM on tap
            return false;        // Return false to ignore further processing of key
        }
        break;
    case LALT_T(KC_AMPR):
        if (record->tap.count && record->event.pressed) {
            tap_code16(KC_AMPR); // Send KC_AMPR on tap
            return false;        // Return false to ignore further processing of key
        }
        break;
    case LGUI_T(KC_LPRN):
        if (record->tap.count && record->event.pressed) {
            tap_code16(KC_LPRN); // Send KC_LPRN on tap
            return false;        // Return false to ignore further processing of key
        }
        break;
    case LSFT_T(KC_RPRN):
        if (record->tap.count && record->event.pressed) {
            tap_code16(KC_RPRN); // Send KC_RPRN on tap
            return false;        // Return false to ignore further processing of key
        }
        break;
    case RSFT_T(KC_MINS):
        if (record->tap.count && record->event.pressed) {
            tap_code16(KC_MINS); // Send KC_MINS on tap
            return false;        // Return false to ignore further processing of key
        }
        break;
    case RGUI_T(KC_EQL):
        if (record->tap.count && record->event.pressed) {
            tap_code16(KC_EQL); // Send KC_EQL on tap
            return false;        // Return false to ignore further processing of key
        }
        break;
    case RALT_T(KC_PLUS):
        if (record->tap.count && record->event.pressed) {
            tap_code16(KC_PLUS); // Send KC_PLUS on tap
            return false;        // Return false to ignore further processing of key
        }
        break;
    case RCTL_T(KC_AT):
        if (record->tap.count && record->event.pressed) {
            tap_code16(KC_AT); // Send KC_AT on tap
            return false;        // Return false to ignore further processing of key
        }
        break;
    }
  return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Qwerty
    * ,-----------------------------------------------------------------------------------.
    * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |ESCNAV|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |shfent|
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |  fn  | Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
    * `-----------------------------------------------------------------------------------'
    */
	[LYR_ALPHA] = LAYOUT_ortho_4x12(
        KC_Q, KC_W, KC_E, KC_R, KC_T, KC_NO, KC_NO, KC_Y, KC_U, KC_I, KC_O, KC_P,
        LCTL_T(KC_A), LALT_T(KC_S), LGUI_T(KC_D), LSFT_T(KC_F), KC_G, KC_NO, KC_NO, KC_H, RSFT_T(KC_J), RGUI_T(KC_K), RALT_T(KC_L), RCTL_T(KC_QUOT),
        KC_Z, KC_X, KC_C, KC_V, KC_B, KC_NO, KC_NO, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
        KC_NO, KC_NO, MO(3), LT(0, KC_LWR), KC_SPC, KC_NO, KC_NO, KC_BSPC, LT(0, KC_RSE), KC_TAB, KC_NO, KC_NO
    ),

	[LYR_LOWER] = LAYOUT_ortho_4x12(
        KC_ESC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        LCTL_T(KC_EXLM), LALT_T(KC_AMPR), LGUI_T(KC_LPRN), LSFT_T(KC_RPRN), KC_GRV, KC_NO, KC_NO, KC_PIPE, RSFT_T(KC_MINS), RGUI_T(KC_EQL), RALT_T(KC_PLUS), RCTL_T(KC_AT),
        KC_HASH, KC_DLR, KC_LCBR, KC_RCBR, KC_PERC, KC_NO, KC_NO, KC_BSLS, KC_LBRC, KC_RBRC, KC_ASTR, KC_UNDS,
        KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO
    ),

	[LYR_RAISE] = LAYOUT_ortho_4x12(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_HOME, KC_UP, KC_END, KC_PGUP,
        KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO
    ),

    [LYR_NUMBLOCK] = LAYOUT_ortho_4x12(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_7, KC_8, KC_9, KC_NO,
        KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_4, KC_5, KC_6, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_0, KC_1, KC_2, KC_3, KC_NO,
        KC_NO, KC_NO, KC_TRNS, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO
    ),

    [LYR_ADJUST] = LAYOUT_ortho_4x12(
        KC_NO, KC_NO, KC_NO, AG_SWAP, AG_NORM, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, QK_BOOT,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD,
        KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO
    )


};
