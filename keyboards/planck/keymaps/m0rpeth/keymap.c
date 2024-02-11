#include QMK_KEYBOARD_H

enum layers {
    LYR_QWERTY = 0,
    LYR_NAV,
    LYR_SYM,
    LYR_FN,
    LYR_ADJUST,
};

enum custom_keycodes {
	KC_NAV = SAFE_RANGE,
	KC_SYM,
	KC_ADJUST,
};

#define LT_SYM MO(LYR_SYM)
#define LT_NAV LT(LYR_NAV, KC_SPC)
#define MT_ESC LGUI_T(KC_ENT)
#define MT_ENT RGUI_T(KC_ENT)
#define OS_FN OSL(LYR_FN)

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
    static uint8_t saved_mods   = 0;

    switch (keycode) {
        case KC_BSPC:
            if (record->event.pressed) {
                saved_mods = get_mods() & MOD_MASK_SHIFT;

                if (saved_mods == MOD_MASK_SHIFT) {  // Both shifts pressed
                    register_code(KC_DEL);
                } else if (saved_mods) {   // One shift pressed
                    del_mods(saved_mods);  // Remove any Shifts present
                    register_code(KC_DEL);
                    add_mods(saved_mods);  // Add shifts again
                } else {
                    register_code(KC_BSPC);
                }
            } else {
                unregister_code(KC_DEL);
                unregister_code(KC_BSPC);
            }
            return false;

      //case LT_NAV:
      //    if (record->event.pressed) {
      //        // on hold
      //        layer_on(LYR_NAV);
      //        update_tri_layer(LYR_NAV, LYR_SYM, LYR_ADJUST);
      //    } else {
      //        // on release
      //        layer_off(LYR_NAV);
      //        update_tri_layer(LYR_NAV, LYR_SYM, LYR_ADJUST);
      //    }
      //    return false;

      //case LT_SYM:
      //    if (record->event.pressed) {
      //        // on hold
      //        layer_on(LYR_SYM);
      //        update_tri_layer(LYR_NAV, LYR_SYM, LYR_ADJUST);
      //    } else {
      //        // on release
      //        layer_off(LYR_SYM);
      //        update_tri_layer(LYR_NAV, LYR_SYM, LYR_ADJUST);
      //    }
      //    return false;
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LYR_QWERTY] = LAYOUT_ortho_4x12(
        KC_ESC,     KC_Q,       KC_W,       KC_E,       KC_R,      KC_T,      KC_Y,      KC_U,      KC_I,       KC_O,       KC_P,       KC_BSPC,
        KC_TAB,     KC_A,       KC_S,       KC_D,       KC_F,      KC_G,      KC_H,      KC_J,      KC_K,       KC_L,       KC_SCLN,    KC_QUOT,
        KC_LSFT,    KC_Z,       KC_X,       KC_C,       KC_V,      KC_B,      KC_N,      KC_M,      KC_COMM,    KC_DOT,     KC_SLSH,    KC_RSFT,
        KC_LCTL,    OS_FN,      KC_LALT,    KC_LGUI,    LT_NAV,    KC_SPC,    KC_SPC,    LT_SYM,    MT_ENT,     KC_RALT,    QK_LEAD,    KC_RCTL
    ),
    // add macro layer? screenshot etc
    [LYR_NAV] = LAYOUT_ortho_4x12(
        KC_TRNS,    KC_COMM,    KC_7,       KC_8,       KC_9,       KC_DLR,     KC_HOME,   KC_PGDN,    KC_PGUP,    KC_END,      KC_NO,      KC_TRNS,
        KC_NO,      KC_0,       KC_4,       KC_5,       KC_6,       KC_PERC,    KC_LEFT,   KC_DOWN,    KC_UP,      KC_RIGHT,    KC_NO,      KC_NO,
        KC_TRNS,    KC_DOT,     KC_1,       KC_2,       KC_3,       KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,       KC_NO,      KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,     KC_TRNS,    KC_TRNS
    ),
    [LYR_SYM] = LAYOUT_ortho_4x12(
        KC_NO,      KC_NO,      KC_PERC,    KC_LBRC,    KC_RBRC,    KC_GRV,     KC_CIRC,    KC_SLSH,    KC_DLR,     KC_ASTR,    KC_HASH,    KC_TRNS,
        KC_NO,      KC_QUES,    KC_EXLM,    KC_LPRN,    KC_RPRN,    KC_PIPE,    KC_AT,      KC_MINS,    KC_EQL,     KC_PLUS,    KC_COLN,    KC_NO,
        KC_NO,      KC_AMPR,    KC_UNDS,    KC_LCBR,    KC_RCBR,    KC_NO,      KC_BSLS,    KC_TILD,    KC_LT,      KC_GT,      KC_DQUO,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS
    ),
    [LYR_FN] = LAYOUT_ortho_4x12(
        KC_NO,    KC_NO,      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_F9,    KC_F10,    KC_F11,    KC_F12,    QK_BOOT,
        KC_NO,    KC_NO,      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_F5,    KC_F6,     KC_F7,     KC_F8,     KC_NO,
        KC_NO,    KC_NO,      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_F1,    KC_F2,     KC_F3,     KC_F4,     KC_NO,
        KC_NO,    KC_TRNS,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,     KC_NO,     KC_NO,     KC_NO
    ),
    [LYR_ADJUST] = LAYOUT_ortho_4x12(
        KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,      KC_NO,    KC_NO,    KC_NO,      KC_NO,       KC_NO,      KC_NO,      QK_BOOT,
        KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,      KC_NO,    KC_NO,    RGB_TOG,    RGB_MOD,     RGB_HUI,    RGB_SAI,    RGB_VAI,
        KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,      KC_NO,    KC_NO,    KC_NO,      RGB_RMOD,    RGB_HUD,    RGB_SAD,    RGB_VAD,
        KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_TRNS,    KC_NO,    KC_NO,    KC_TRNS,    KC_NO,       KC_NO,      KC_NO,      KC_NO
    )
};
