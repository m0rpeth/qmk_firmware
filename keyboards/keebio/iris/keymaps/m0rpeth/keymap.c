#include QMK_KEYBOARD_H

LEADER_EXTERNS();

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

//void matrix_scan_user(void) {
//  LEADER_DICTIONARY() {
//
//    leading = false;
//
//    SEQ_ONE_KEY(KC_F) {
//      // Anything you can do in a macro.
//      SEND_STRING("QMK is awesome.");
//    }
//
//    SEQ_TWO_KEYS(KC_D, KC_D) {
//      SEND_STRING(SS_LCTL("a") SS_LCTL("c"));
//    }
//
//    SEQ_TWO_KEYS(KC_A, KC_S) {
//      register_code(KC_LGUI);
//      register_code(KC_S);
//      unregister_code(KC_S);
//      unregister_code(KC_LGUI);
//    }
//
//    SEQ_THREE_KEYS(KC_D, KC_D, KC_S) {
//      SEND_STRING("https://start.duckduckgo.com\n");
//    }
//
//  }
//}

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
    [LYR_ALPHA] = LAYOUT(
        //┌────────┬────────┬────────┬────────┬────────┬────────┐                            ┌────────┬────────┬────────┬────────┬────────┬────────┐
            KC_F24,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                                KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                            ├────────┼────────┼────────┼────────┼────────┼────────┤
            QK_LEAD,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                                 KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_NO,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                            ├────────┼────────┼────────┼────────┼────────┼────────┤
            KC_NO,  LCTL_T(KC_A), LALT_T(KC_R), LGUI_T(KC_S), LSFT_T(KC_T), KC_D,             KC_H, RSFT_T(KC_N), RGUI_T(KC_E), RALT_T(KC_I), RCTL_T(KC_O), KC_QUOT,
        //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐          ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            KC_NO,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_ESC,             KC_DEL,  KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_NO,
        //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘          └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                           KC_NBL,  LT(0, KC_LWR),  KC_SPC,               KC_BSPC, LT(0, KC_RSE),  KC_TAB
        //                               └────────┴────────┴────────┘                   └────────┴────────┴────────┘
    ),

    [LYR_LOWER] = LAYOUT(
        //┌────────┬────────┬────────┬────────┬────────┬────────┐                            ┌────────┬────────┬────────┬────────┬────────┬────────┐
            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                                KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                            ├────────┼────────┼────────┼────────┼────────┼────────┤
            KC_NO,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                 KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_NO,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                            ├────────┼────────┼────────┼────────┼────────┼────────┤
            KC_NO,   LCTL_T(KC_EXLM), LALT_T(KC_AMPR), LGUI_T(KC_LPRN), LSFT_T(KC_RPRN), KC_GRV,                       KC_PIPE, RSFT_T(KC_MINS), RGUI_T(KC_EQL), RALT_T(KC_PLUS), RCTL_T(KC_AT), KC_NO,
        //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐          ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            KC_NO,   KC_HASH, KC_DLR,  KC_LCBR, KC_RCBR, KC_PERC, KC_NO,              KC_TRNS, KC_BSLS, KC_LBRC, KC_RBRC, KC_ASTR, KC_UNDS, KC_NO,
        //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘          └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                           KC_NO,   KC_TRNS, KC_NO,                       KC_TRNS, KC_TRNS, KC_NO
        //                               └────────┴────────┴────────┘                   └────────┴────────┴────────┘
    ),

    [LYR_RAISE] = LAYOUT(
        //┌────────┬────────┬────────┬────────┬────────┬────────┐                            ┌────────┬────────┬────────┬────────┬────────┬────────┐
            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                                KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                            ├────────┼────────┼────────┼────────┼────────┼────────┤
            KC_NO,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_NO,                                KC_NO,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NO,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                            ├────────┼────────┼────────┼────────┼────────┼────────┤
            KC_NO,   KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_NO,                                KC_NO,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_NO,
        //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐          ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_NO,   KC_NO,              KC_TRNS, KC_NO,   KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_NO,
        //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘          └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                           KC_NO,   KC_TRNS, KC_NO,                       KC_TRNS, KC_TRNS, KC_NO
        //                               └────────┴────────┴────────┘                   └────────┴────────┴────────┘
    ),

    [LYR_NUMBLOCK] = LAYOUT(
        //┌────────┬────────┬────────┬────────┬────────┬────────┐                            ┌────────┬────────┬────────┬────────┬────────┬────────┐
            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                                KC_NO,   KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS, KC_NO,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                            ├────────┼────────┼────────┼────────┼────────┼────────┤
            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                                KC_NO,   KC_P7,   KC_P8,   KC_P9,   KC_PPLS, KC_NO,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                            ├────────┼────────┼────────┼────────┼────────┼────────┤
            KC_NO,   KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_NO,                                KC_NO,   KC_P4,   KC_P5,   KC_P6,   KC_PCMM, KC_NO,
        //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐          ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,              KC_TRNS, KC_NO,   KC_P1,   KC_P2,   KC_P3,   KC_PEQL, KC_NO,
        //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘          └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                           KC_TRNS, KC_NO,   KC_NO,                       KC_TRNS, KC_P0,   KC_PDOT
        //                               └────────┴────────┴────────┘                   └────────┴────────┴────────┘
    ),

    [LYR_ADJUST] = LAYOUT(
        //┌────────┬────────┬────────┬────────┬────────┬────────┐                            ┌────────┬────────┬────────┬────────┬────────┬────────┐
            KC_NO,   KC_NO,   KC_NO,   KC_NO,   AG_SWAP, AG_NORM,                              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   QK_BOOT,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                            ├────────┼────────┼────────┼────────┼────────┼────────┤
            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                                BL_INC,  RGB_MOD, RGB_SPI, RGB_HUI, RGB_SAI, RGB_VAI,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                            ├────────┼────────┼────────┼────────┼────────┼────────┤
            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                                BL_TOGG, RGB_TOG, KC_NO,   KC_NO,   KC_NO,   KC_NO,
        //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐          ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,              KC_NO,   BL_DEC, RGB_RMOD, RGB_SPD, RGB_HUD, RGB_SAD, RGB_VAD,
        //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘          └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                           KC_NO,   KC_TRNS, KC_NO,                       KC_NO,   KC_TRNS, KC_NO
        //                               └────────┴────────┴────────┘                   └────────┴────────┴────────┘
    )
};
