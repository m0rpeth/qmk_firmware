#include QMK_KEYBOARD_H
#include "features/achordion.h"

enum layers {
    LYR_QWERTY = 0,
    LYR_NAV,
    LYR_SYM,
    LYR_ADJ,
    LYR_FN,
};

// screenshot macro?

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

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, LYR_NAV, LYR_SYM, LYR_ADJ);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_achordion(keycode, record)) { return false; }

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
    }
    return true;
};

void matrix_scan_user(void) {
  achordion_task();
}

bool achordion_chord(uint16_t tap_hold_keycode,
                     keyrecord_t* tap_hold_record,
                     uint16_t other_keycode,
                     keyrecord_t* other_record) {
  // follow the opposite hands rule.
  return achordion_opposite_hands(tap_hold_record, other_record);
}

#define MO_NAV MO(LYR_NAV)
#define MO_SYM MO(LYR_SYM)

#define OS_FN OSL(LYR_FN)

#define LT_LSFT LSFT_T(KC_F)
#define LT_LGUI LGUI_T(KC_D)
#define LT_LALT LALT_T(KC_S)
#define LT_LCTL LCTL_T(KC_A)

#define LT_RSFT RSFT_T(KC_J)
#define LT_RGUI RGUI_T(KC_K)
#define LT_RALT RALT_T(KC_L)
#define LT_RCTL RCTL_T(KC_SCLN)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LYR_QWERTY] = LAYOUT_split_4x6_5(
        KC_NO,      KC_1,    KC_2,      KC_3,       KC_4,       KC_5,                   KC_6,       KC_7,       KC_8,       KC_9,      KC_0,       KC_NO,
        KC_NO,      KC_Q,    KC_W,      KC_E,       KC_R,       KC_T,                   KC_Y,       KC_U,       KC_I,       KC_O,      KC_P,       KC_BSPC,
        KC_TAB,     LT_LCTL, LT_LALT,   LT_LGUI,    LT_LSFT,    KC_G,                   KC_H,       LT_RSFT,    LT_RGUI,    LT_RALT,   LT_RCTL,    KC_QUOT,
        KC_NO,      KC_Z,    KC_X,      KC_C,       KC_V,       KC_B,                   KC_N,       KC_M,       KC_COMM,    KC_DOT,    KC_SLSH,    KC_NO,

                                        MO(1),      KC_BSPC,    KC_ESC,                 KC_ENT,     KC_SPC,     MO(2),
                                                    KC_ESC,     KC_NO,                  KC_NO,      KC_ENT
    ),
    [LYR_SYM] = LAYOUT_split_4x6_5(
        KC_NO,      KC_TRNS, KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,                KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,   KC_TRNS,    KC_NO,
        KC_NO,      KC_NO,   KC_PERC,   KC_LBRC,    KC_RBRC,    KC_GRV,                 KC_CIRC,    KC_SLSH,    KC_DLR,     KC_ASTR,   KC_HASH,    KC_NO,
        KC_NO,      KC_QUES, KC_EXLM,   KC_LPRN,    KC_RPRN,    KC_PIPE,                KC_AT,      KC_MINS,    KC_EQL,     KC_PLUS,   KC_COLN,    KC_NO,
        KC_NO,      KC_AMPR, KC_UNDS,   KC_LCBR,    KC_RCBR,    KC_NO,                  KC_BSLS,    KC_TILD,    KC_LT,      KC_GT,     KC_DQUO,    KC_TRNS,

                                        KC_TRNS,    KC_TRNS,    KC_TRNS,                KC_TRNS,    KC_TRNS,    KC_TRNS,
                                                    KC_TRNS,    KC_TRNS,                KC_TRNS,    KC_TRNS
    ),
    [LYR_NAV] = LAYOUT_split_4x6_5(
        KC_NO,      KC_TRNS, KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,                KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,   KC_TRNS,    KC_NO,
        KC_NO,      KC_COMM, KC_7,      KC_8,       KC_9,       KC_DLR,                 KC_HOME,    KC_PGUP,    KC_PGDN,    KC_END,    KC_NO,      KC_NO,
        KC_TRNS,    KC_0,    KC_4,      KC_5,       KC_6,       KC_PERC,                KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT,  KC_NO,      KC_NO,
        KC_NO,      KC_DOT,  KC_1,      KC_2,       KC_3,       KC_NO,                  KC_NO,      KC_NO,      KC_NO,      KC_NO,     KC_NO,      KC_NO,

                                        KC_TRNS,    KC_TRNS,    KC_TRNS,                KC_TRNS,    KC_TRNS,    KC_TRNS,
                                                    KC_TRNS,    KC_TRNS,                KC_TRNS,    KC_TRNS
    ),
    [LYR_ADJ] = LAYOUT_split_4x6_5(
        KC_NO,      KC_NO,   KC_NO,     KC_NO,      KC_NO,      KC_NO,                  KC_NO,      KC_NO,      KC_NO,      KC_NO,     KC_NO,      QK_BOOT,
        KC_NO,      KC_NO,   KC_NO,     KC_NO,      KC_NO,      KC_NO,                  KC_NO,      KC_NO,      KC_NO,      KC_NO,     KC_NO,      KC_NO,
        KC_NO,      KC_NO,   KC_NO,     KC_NO,      KC_NO,      KC_NO,                  KC_NO,      KC_NO,      KC_NO,      KC_NO,     KC_NO,      KC_NO,
        KC_NO,      KC_NO,   KC_NO,     KC_NO,      KC_NO,      KC_NO,                  KC_NO,      KC_NO,      KC_NO,      KC_NO,     KC_NO,      KC_NO,

                                        KC_TRNS,    KC_TRNS,    KC_TRNS,                KC_TRNS,    KC_TRNS,    KC_TRNS,
                                                    KC_TRNS,    KC_TRNS,                KC_TRNS,    KC_TRNS
    ),
    [LYR_FN] = LAYOUT_split_4x6_5(
        KC_NO,      KC_NO,   KC_NO,     KC_NO,      KC_NO,      KC_NO,                  KC_NO,      KC_NO,      KC_NO,      KC_NO,     KC_NO,      KC_NO,
        KC_NO,      KC_NO,   KC_NO,     KC_NO,      KC_NO,      KC_NO,                  KC_NO,      KC_NO,      KC_NO,      KC_NO,     KC_NO,      KC_NO,
        KC_F1,      KC_F2,   KC_F3,     KC_F4,      KC_F5,      KC_F6,                  KC_F7,      KC_F8,      KC_F9,      KC_F10,    KC_F11,     KC_F12,
        KC_NO,      KC_NO,   KC_NO,     KC_NO,      KC_NO,      KC_NO,                  KC_NO,      KC_NO,      KC_NO,      KC_NO,     KC_NO,      KC_NO,

                                        KC_TRNS,    KC_TRNS,    KC_TRNS,                KC_TRNS,    KC_TRNS,    KC_TRNS,
                                                    KC_TRNS,    KC_TRNS,                KC_TRNS,    KC_TRNS
    )
};
