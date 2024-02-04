#include QMK_KEYBOARD_H

enum layers {
    LYR_QWERTY = 0,
    LYR_LOWER,
    LYR_RAISE,
    LYR_FN,
    LYR_ADJUST,
};

enum custom_keycodes {
	KC_LWR = SAFE_RANGE,
	KC_RSE,
	KC_ADJUST,
};

#define LT_LWR LT(0, KC_LWR)
#define LT_RSE LT(0, KC_RSE)

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

        case LT_LWR:
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

        case LT_RSE:
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
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LYR_QWERTY] = LAYOUT(
        KC_EQL,     KC_1,    KC_2,      KC_3,       KC_4,       KC_5,                   KC_6,       KC_7,       KC_8,       KC_9,      KC_0,       KC_MINS,
        KC_TAB,     KC_Q,    KC_W,      KC_E,       KC_R,       KC_T,                   KC_Y,       KC_U,       KC_I,       KC_O,      KC_P,       KC_BSLS,
        KC_ESC,     KC_A,    KC_S,      KC_D,       KC_F,       KC_G,                   KC_H,       KC_J,       KC_K,       KC_L,      KC_SCLN,    KC_QUOT,
        KC_LSFT,    KC_Z,    KC_X,      KC_C,       KC_V,       KC_B,                   KC_N,       KC_M,       KC_COMM,    KC_DOT,    KC_SLSH,    KC_RSFT,
        KC_NO,      KC_GRV,  KC_CAPS,   KC_LEFT,    KC_RGHT,    KC_LCTL,                KC_RCTL,    KC_UP,      KC_DOWN,    KC_LBRC,   KC_RBRC,    KC_NO,
        KC_NO,      KC_BSPC, KC_DEL,    KC_END,     KC_HOME,    KC_LALT,                KC_RGUI,    KC_PGUP,    KC_PGDN,    KC_ENT,    KC_SPC,     KC_NO
    )
};
