#include QMK_KEYBOARD_H

enum layers {
    LYR_QWERTY = 0,
    LYR_COLEMAK,
    LYR_LOWER,
    LYR_RAISE,
    LYR_ADJUST
};

enum custom_keycodes {
	KC_LWR = SAFE_RANGE,
	KC_RSE,
	KC_ADJUST,
    KC_RAISE_MOD,
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
    static uint8_t saved_mods   = 0;
    static bool raise_mod_is_held = false;

    switch (keycode) {
        case KC_RAISE_MOD:
            raise_mod_is_held = record->event.pressed;
            break;
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

        case KC_LPRN:
            {
                static int registered_key = KC_NO;
                if (record->event.pressed) {
                    add_mods(MOD_LSFT);
                    registered_key = (raise_mod_is_held) ? KC_LT : KC_LPRN;
                    register_code(registered_key);
                } else {
                    unregister_code(registered_key);
                    registered_key = KC_NO;
                    if (get_mods() & MOD_MASK_SHIFT) {
                        del_mods(MOD_LSFT);
                    }
                }
            }
            return false;

        case KC_RPRN:
            {
                static int registered_key = KC_NO;
                if (record->event.pressed) {
                    add_mods(MOD_LSFT);
                    registered_key = (raise_mod_is_held) ? KC_GT : KC_RPRN;
                    register_code(registered_key);
                } else {
                    unregister_code(registered_key);
                    registered_key = KC_NO;
                    if (get_mods() & MOD_MASK_SHIFT) {
                        del_mods(MOD_LSFT);
                    }
                }
            }
            return false;

        case KC_LCBR:
            {
                static int registered_key = KC_NO;
                if (record->event.pressed) {
                    if (raise_mod_is_held) {
                        registered_key = KC_LBRC;
                        register_code(registered_key);
                    } else {
                        registered_key = KC_LCBR;
                        add_mods(MOD_LSFT);
                        register_code(registered_key);
                    }
                } else {
                    unregister_code(registered_key);
                    registered_key = KC_NO;
                    if (get_mods() & MOD_MASK_SHIFT) {
                        del_mods(MOD_LSFT);
                    }
                }
            }
            return false;

        case KC_RCBR:
            {
                static int registered_key = KC_NO;
                if (record->event.pressed) {
                    if (raise_mod_is_held) {
                        registered_key = KC_RBRC;
                        register_code(registered_key);
                    } else {
                        registered_key = KC_RCBR;
                        add_mods(MOD_LSFT);
                        register_code(registered_key);
                    }
                } else {
                    unregister_code(registered_key);
                    registered_key = KC_NO;
                    if (get_mods() & MOD_MASK_SHIFT) {
                        del_mods(MOD_LSFT);
                    }
                }
            }
            return false;

    }
    return true;
}

#define LT_LWR LT(0, KC_LWR)
#define LT_RSE LT(0, KC_RSE)
#define RG_ENT RGUI_T(KC_ENT)
#define TG_COL TG(LYR_COLEMAK)

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

    [LYR_QWERTY] = LAYOUT_ortho_4x12(
        KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
        KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
        KC_LCTL, KC_LALT, QK_LEAD, KC_LGUI, LT_LWR, KC_BSPC, KC_SPC, LT_RSE, RG_ENT, QK_LEAD, KC_RALT, KC_RCTL
    ),
    [LYR_COLEMAK] = LAYOUT_ortho_4x12(
        KC_TRNS, KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_TRNS,
        KC_TRNS, KC_A, KC_R, KC_S, KC_T, KC_D, KC_H, KC_N, KC_E, KC_I, KC_O, KC_QUOT,
        KC_TRNS, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_K, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [LYR_LOWER] = LAYOUT_ortho_4x12(
        KC_NO, KC_HOME, KC_UP, KC_END, KC_PGUP, KC_NO, KC_NO, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS,
        KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_NO, KC_NO, KC_F5, KC_F6, KC_F7, KC_F8, KC_NO,
        KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [LYR_RAISE] = LAYOUT_ortho_4x12(
        KC_TILD, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_TRNS,
        KC_HASH, KC_EXLM, KC_AMPR, KC_LPRN, KC_RPRN, KC_GRV, KC_PIPE, KC_MINS, KC_EQL, KC_PLUS, KC_COLN, KC_DQUO,
        KC_RAISE_MOD, KC_QUES, KC_AT, KC_LCBR, KC_RCBR, KC_PERC, KC_CIRC, KC_DLR, KC_ASTR, KC_BSLS, KC_UNDS, KC_RAISE_MOD,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [LYR_ADJUST] = LAYOUT_ortho_4x12(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, QK_BOOT,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD,
        TG_COL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
};
