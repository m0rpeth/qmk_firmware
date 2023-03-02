#include QMK_KEYBOARD_H

enum layers {
    LYR_ALPHA = 0,
    LYR_COLEMAK,
    LYR_LOWER,
    LYR_RAISE,
    LYR_ADJUST
};

enum custom_keycodes {
	KC_LWR = SAFE_RANGE,
	KC_RSE,
	KC_ADJUST
};

void leader_end_user(void) {
    if (leader_sequence_one_key(KC_M)) {
        register_code(KC_F24);
        unregister_code(KC_F24);
    }
    else if (leader_sequence_two_keys(KC_S, KC_S)) {
        register_code(KC_LCTL);
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        register_code(KC_4);
        unregister_code(KC_LCTL);
        unregister_code(KC_LGUI);
        unregister_code(KC_LSFT);
        unregister_code(KC_4);
    }
}

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
        if (record->event.pressed) {
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

    [LYR_ALPHA] = LAYOUT(
        //┌────────┬────────┬────────┬────────┬────────┬────────┐                            ┌────────┬────────┬────────┬────────┬────────┬────────┐
            QK_LEAD, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                 KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   KC_NO,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                            ├────────┼────────┼────────┼────────┼────────┼────────┤
            KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                 KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,   KC_DEL,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                            ├────────┼────────┼────────┼────────┼────────┼────────┤
            KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                 KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐          ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_LCTL,             KC_ENT,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘          └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                           KC_LALT, KC_LGUI, KC_BSPC,                     KC_SPC,  LT(0, KC_RSE), LT(0, KC_LWR)
        //                               └────────┴────────┴────────┘                   └────────┴────────┴────────┘
    ),

    [LYR_COLEMAK] = LAYOUT(
        //┌────────┬────────┬────────┬────────┬────────┬────────┐                            ┌────────┬────────┬────────┬────────┬────────┬────────┐
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                              KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                            ├────────┼────────┼────────┼────────┼────────┼────────┤
            KC_TRNS, KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                                 KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_TRNS,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                            ├────────┼────────┼────────┼────────┼────────┼────────┤
            KC_TRNS, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                                 KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_TRNS,
        //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐          ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            KC_TRNS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_TRNS,             KC_TRNS, KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_TRNS,
        //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘          └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                           KC_TRNS, KC_TRNS, KC_TRNS,                     KC_TRNS, KC_TRNS, KC_TRNS
        //                               └────────┴────────┴────────┘                   └────────┴────────┴────────┘
    ),

    [LYR_LOWER] = LAYOUT(
        //┌────────┬────────┬────────┬────────┬────────┬────────┐                            ┌────────┬────────┬────────┬────────┬────────┬────────┐
            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                                KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                            ├────────┼────────┼────────┼────────┼────────┼────────┤
            KC_NO,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NO,                                KC_NO,   KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_NO,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                            ├────────┼────────┼────────┼────────┼────────┼────────┤
            KC_NO,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_NO,                                KC_NO,   KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_NO,
        //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐          ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_NO,  KC_TRNS,            KC_TRNS,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘          └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                          KC_TRNS, KC_TRNS, KC_TRNS,                     KC_TRNS, KC_TRNS, KC_TRNS
        //                               └────────┴────────┴────────┘                   └────────┴────────┴────────┘
    ),

    [LYR_RAISE] = LAYOUT(
        //┌────────┬────────┬────────┬────────┬────────┬────────┐                            ┌────────┬────────┬────────┬────────┬────────┬────────┐
            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                                KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                            ├────────┼────────┼────────┼────────┼────────┼────────┤
            KC_CIRC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                 KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DLR,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                            ├────────┼────────┼────────┼────────┼────────┼────────┤
            KC_HASH, KC_EXLM, KC_AMPR, KC_LPRN, KC_RPRN, KC_GRV,                               KC_PIPE, KC_MINS, KC_EQL,  KC_PLUS, KC_COLN, KC_DQUO,
        //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐          ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            KC_LT,   KC_QUES, KC_AT,   KC_LCBR, KC_RCBR, KC_PERC, KC_TRNS,           KC_TRNS,  KC_BSLS, KC_LBRC, KC_RBRC, KC_ASTR, KC_UNDS, KC_GT,
        //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘          └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                           KC_TRNS, KC_TRNS, KC_TRNS,                     KC_TRNS, KC_TRNS, KC_TRNS
        //                               └────────┴────────┴────────┘                   └────────┴────────┴────────┘
    ),

    [LYR_ADJUST] = LAYOUT(
        //┌────────┬────────┬────────┬────────┬────────┬────────┐                            ┌────────┬────────┬────────┬────────┬────────┬────────┐
            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                                KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   QK_BOOT,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                            ├────────┼────────┼────────┼────────┼────────┼────────┤
            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                                BL_STEP, RGB_MOD, RGB_SPI, RGB_HUI, RGB_SAI, RGB_VAI,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                            ├────────┼────────┼────────┼────────┼────────┼────────┤
            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                                BL_TOGG, RGB_TOG, KC_NO,   KC_NO,   KC_NO,   KC_NO,
        //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐          ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            TG(1),   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,              KC_NO,   BL_STEP, RGB_RMOD, RGB_SPD, RGB_HUD, RGB_SAD, RGB_VAD,
        //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘          └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                           KC_NO,   KC_NO,   KC_NO,                       KC_NO,   KC_TRNS, KC_TRNS
        //                               └────────┴────────┴────────┘                   └────────┴────────┴────────┘
    )
};
