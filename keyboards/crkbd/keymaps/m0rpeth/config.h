#pragma once

#define OLED_DISPLAY_128x32

#define ONESHOT_TAP_TOGGLE 20                       // Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TIMEOUT 5000                        // Time (in ms) before the one shot key is released */

#define MK_3_SPEED                                  // constant mouse-speed mode, no acceleration

#define COMBO_TERM 50
#define COMBO_MUST_HOLD_MODS

//#define QUICK_TAP_TERM ???

#define TAPPING_TERM 190
#define PERMISSIVE_HOLD

#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 1000

#define AUTO_SHIFT_TIMEOUT 165

//#define NO_AUTO_SHIFT_ALPHA                         // disallow alphas to be auto shifted
//#define NO_AUTO_SHIFT_NUMERIC                     // disallow 1234567890 to be auto shifted
//#define NO_AUTO_SHIFT_SPECIAL                     // disallow -_, =+, [{, ]}, ;:, ‘“, ,<, .>, and /? to be auto shifted

//
// save some space ...
//
#ifndef NO_DEBUG
#define NO_DEBUG
#endif

#define SPLIT_LAYER_STATE_ENABLE
#define IS_RIGHT_SIDE_FIRMWARE
