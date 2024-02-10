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
#define MT_ENT RGUI_T(KC_ENT)

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
}

// const uint16_t PROGMEM ampr_combo[] = {KC_Q, KC_W, COMBO_END}; // & => q + w
// const uint16_t PROGMEM ques_combo[] = {KC_A, KC_S, COMBO_END}; // ? => a + s
// const uint16_t PROGMEM exlm_combo[] = {KC_Z, KC_X, COMBO_END}; // ! => z + x
//
// const uint16_t PROGMEM grv_combo[] = {KC_R, KC_T, COMBO_END}; // [ => r + t
// const uint16_t PROGMEM at_combo[] = {KC_F, KC_G, COMBO_END}; // [ => f + g
// const uint16_t PROGMEM perc_combo[] = {KC_V, KC_B, COMBO_END}; // [ => v + b
//
// const uint16_t PROGMEM lbrc_combo[] = {KC_W, KC_E, COMBO_END}; // [ => w + e
// const uint16_t PROGMEM lprn_combo[] = {KC_S, KC_D, COMBO_END}; // ( => s + d
// const uint16_t PROGMEM lcbr_combo[] = {KC_X, KC_C, COMBO_END}; // { => x + c
//
// const uint16_t PROGMEM rbrc_combo[] = {KC_E, KC_R, COMBO_END}; // ] => e + r
// const uint16_t PROGMEM rprn_combo[] = {KC_D, KC_F, COMBO_END}; // ) => d + f
// const uint16_t PROGMEM rcbr_combo[] = {KC_C, KC_V, COMBO_END}; // } => c + v
//
// const uint16_t PROGMEM eqls_combo[] = {KC_K, KC_L, COMBO_END}; // = => k + l
// const uint16_t PROGMEM gt_combo[] = {KC_L, KC_SCLN, COMBO_END}; // > => l + scln


//combo_t key_combos[] = {
    //COMBO(ampr_combo, KC_AMPR),
    //COMBO(ques_combo, KC_QUES),
    //COMBO(exlm_combo, KC_EXLM),

    //COMBO(grv_combo, KC_GRV),
    //COMBO(at_combo, KC_AT),
    //COMBO(perc_combo, KC_PERC),

    //COMBO(lbrc_combo, KC_LBRC),
    //COMBO(lprn_combo, KC_LPRN),
    //COMBO(lcbr_combo, KC_LCBR),
    //COMBO(rbrc_combo, KC_RBRC),
    //COMBO(rprn_combo, KC_RPRN),
    //COMBO(rcbr_combo, KC_RCBR),

    //COMBO(eqls_combo, KC_EQL),
    //COMBO(gt_combo, KC_GT),
//};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LYR_QWERTY] = LAYOUT_ortho_4x12(
        KC_ESC,     KC_Q,       KC_W,       KC_E,       KC_R,      KC_T,      KC_Y,      KC_U,      KC_I,       KC_O,       KC_P,       KC_BSPC,
        KC_TAB,     KC_A,       KC_S,       KC_D,       KC_F,      KC_G,      KC_H,      KC_J,      KC_K,       KC_L,       KC_SCLN,    KC_QUOT,
        KC_LSFT,    KC_Z,       KC_X,       KC_C,       KC_V,      KC_B,      KC_N,      KC_M,      KC_COMM,    KC_DOT,     KC_SLSH,    KC_RSFT,
        KC_LCTL,    OSL(3),    KC_LALT,    KC_LGUI,    LT_LWR,    KC_SPC,    KC_SPC,    LT_RSE,    MT_ENT,     KC_RALT,    QK_LEAD,      KC_RCTL
    ),
    [LYR_LOWER] = LAYOUT_ortho_4x12(
        KC_TRNS,    KC_HOME,    KC_PGUP,    KC_PGDN,    KC_END,      KC_NO,      KC_NO,      KC_7,       KC_8,       KC_9,       KC_COMM,    KC_TRNS,
        KC_NO,      KC_LEFT,    KC_UP,      KC_DOWN,    KC_RIGHT,    KC_NO,      KC_PERC,    KC_4,       KC_5,       KC_6,       KC_0,       KC_NO,
        KC_TRNS,    KC_NO,      KC_NO,      KC_NO,      KC_NO,       KC_NO,      KC_DLR,     KC_1,       KC_2,       KC_3,       KC_DOT,     KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,     KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS
    ),
    [LYR_RAISE] = LAYOUT_ortho_4x12(
        KC_NO,      KC_NO,      KC_PERC,    KC_LBRC,    KC_RBRC,    KC_GRV,     KC_CIRC,    KC_SLSH,    KC_DLR,     KC_ASTR,    KC_HASH,    KC_TRNS,
        KC_NO,      KC_QUES,    KC_EXLM,    KC_LPRN,    KC_RPRN,    KC_PIPE,    KC_AT,      KC_MINS,    KC_EQL,     KC_PLUS,    KC_COLN,    KC_NO,
        KC_NO,      KC_AMPR,    KC_UNDS,    KC_LCBR,    KC_RCBR,    KC_NO,      KC_BSLS,    KC_TILD,    KC_LT,      KC_GT,      KC_DQUO,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS
    ),
    [LYR_FN] = LAYOUT_ortho_4x12(
        KC_NO,    KC_NO,      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_F9,    KC_F10,    KC_F11,    KC_F12,    KC_NO,
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
