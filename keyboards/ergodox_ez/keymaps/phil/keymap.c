#include QMK_KEYBOARD_H
#define QMK_KEYS_PER_SCAN 8
#include "action_layer.h"
#include "debug.h"
#include "version.h"

enum layers {
    BASE,  // default layer
    GAME,  // gaming keys
    MDIA,  // media keys
    SYMB,  // symbols
};

enum custom_keycodes {
  VRSN = SAFE_RANGE,  // can always be here
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,----------------------------------------------------.           ,--------------------------------------------------.
 * |   1      |   2  |   3  |   4  |   5  |   6  | LEFT |           |   6  |   7  |   8  |   9  |   0  |   -  |   =    |
 * |----------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab      |   Q  |   W  |   E  |   R  |   T  |  L1  |           |  L3  |   Y  |   U  |   I  |   O  |   P  |   [    |
 * |----------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | BkSp/Ctrl|   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |; / L2|   '    |
 * |----------+------+------+------+------+------| Hyper|           | Meh  |------+------+------+------+------+--------|
 * |Spc/LShift|   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | RShift |
 * `----------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Grv/L1  |  Cmd |   ◀  | ▶/Alt| Enter|                                       |Space |   ]  |   [  |   ]  | ~L1  |
 *   `------------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        | Home | End  |       | PgUp |Ctrl/Esc|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgDn |        |      |
 *                                 | `/L1 | BkSp |------|       |------| Down   |  \   |
 *                                 |      |      |Insert|       |  Up  |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
                   KC_1,    KC_2,    KC_3,            KC_4,  KC_5,  KC_6,      KC_LEFT,
                 KC_TAB,    KC_Q,    KC_W,            KC_E,  KC_R,  KC_T,     TG(SYMB),
         CTL_T(KC_BSPC),    KC_A,    KC_S,            KC_D,  KC_F,  KC_G,
         LSFT_T(KC_SPC),    KC_Z,    KC_X,            KC_C,  KC_V,  KC_B, ALL_T(KC_NO),
        LT(SYMB,KC_GRV), KC_LGUI, KC_LEFT, LALT_T(KC_RGHT), KC_ENT,

                                                      KC_HOME,  KC_END,
                                                               KC_HOME,
                                              KC_BSPC, KC_GRV,  KC_INS,

        // right hand
        KC_6,        KC_7,   KC_8,  KC_9,   KC_0,   KC_MINS,          KC_EQL,
        TG(GAME),    KC_Y,   KC_U,  KC_I,   KC_O,   KC_P,             KC_LBRC,
                     KC_H,   KC_J,  KC_K,   KC_L,   LT(MDIA, KC_SCLN),KC_QUOT,
        MEH_T(KC_NO),KC_N,   KC_M,  KC_COMM,KC_DOT, KC_SLSH,          KC_RSFT,
                             KC_SPC,KC_RBRC,KC_LBRC,KC_RBRC,          TT(SYMB),

        KC_PGUP,       CTL_T(KC_ESC),
        KC_PGDN,
        KC_UP,  KC_DOWN, KC_BSLS
    ),

/* Keymap 1: Symbol Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |   F1    |  F2  |  F3  |  F4  |  F5  |  F6  |      |           |      |  F7  |  F8  |  F9  |  F10 |  F11 |   F12  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  Ctrl   |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  Shift  |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | EPRM  |      |      | Alt  |      |                                       |      |    . |   0  |   =  |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |Scrn  |Scrn  |      |       |      |      |      |
 *                                 |Brt-  |Brt+  |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = LAYOUT_ergodox(
       // left hand
       KC_F1  ,KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_TRNS,
       KC_TRNS,KC_EXLM,KC_AT,  KC_LCBR,KC_RCBR,KC_PIPE,KC_TRNS,
       KC_LCTL,KC_HASH,KC_DLR, KC_LPRN,KC_RPRN,KC_GRV,
       KC_LSFT,KC_PERC,KC_CIRC,KC_LBRC,KC_RBRC,KC_TILD,KC_TRNS,
        EE_CLR,KC_TRNS,KC_TRNS,KC_LALT,KC_TRNS,

                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_BRID,KC_BRIU,KC_TRNS,
       // right hand
       KC_TRNS, KC_F7,   KC_F8,  KC_F9,   KC_F10,  KC_F11,  KC_F12,
       KC_TRNS, KC_UP,   KC_7,   KC_8,    KC_9,    KC_ASTR, KC_TRNS,
                KC_DOWN, KC_4,   KC_5,    KC_6,    KC_PLUS, KC_TRNS,
       KC_TRNS, KC_AMPR, KC_1,   KC_2,    KC_3,    KC_BSLS, KC_TRNS,
                         KC_TRNS,KC_DOT,  KC_0,    KC_EQL,  KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),

/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  Vrsn  |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |ScrlUp|ScrlDn|      |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Mclk | Lclk |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 | Rclk |      |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MDIA] = LAYOUT_ergodox(
       VRSN,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN3, KC_BTN1,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_BTN2, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_TRNS, KC_MPLY,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
                          KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_WBAK
),

/* Keymap 3: Game Layer
 *
 * ,----------------------------------------------------.           ,--------------------------------------------------.
 * |   Esc    |   1  |   2  |   3  |   4  |   5  |   6  |           |   6  |   7  |   8  |   9  |   0  |      |        |
 * |----------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |   Tab    |      |      |      |      |      |      |           | ~L3  |      |      |      |      |      |        |
 * |----------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   Ctrl   |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |----------+------+------+------+------+------| LSymb|           |      |------+------+------+------+------+--------|
 * |  LShift  |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `----------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |   `    |      |      |  Alt | Space|                                       |Enter |      |      |      |      |
 *   `------------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        |      |      |       |      |        |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |      |       |      |        |      |
 *                                 | BkSp |      |------|       |------|        |      |
 *                                 |      |      |      |       |      |        |      |
 *                                 `--------------------'       `----------------------'
 */
[GAME] = LAYOUT_ergodox(  // layer 3 : gaming
        // left hand
        KC_ESC,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,     KC_6,
        KC_TAB,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
        KC_LCTL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_LSFT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(SYMB),
        KC_GRV,  KC_TRNS, KC_TRNS, KC_LALT,  KC_SPC,

                                                      KC_TRNS,KC_TRNS,
                                                              KC_TRNS,
                                              KC_BSPC,KC_TRNS,KC_TRNS,

        // right hand
        KC_6,        KC_7,    KC_8,    KC_9,    KC_0, KC_TRNS, KC_TRNS,
        TG(GAME), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                            KC_ENT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

        KC_TRNS,  KC_TRNS,
        KC_TRNS,
        KC_TRNS,  KC_TRNS, KC_TRNS
    ),
};
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case VRSN:
                SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION " built " QMK_BUILDDATE);
                return false;
            case LT(MDIA, KC_SCLN):
                // If the user is holding a modifier key, then we don't want to
                // switch layers.
                if ((get_mods() & (MOD_MASK_CTRL | MOD_MASK_SHIFT)) != 0) {
                  register_code(KC_SCLN);
                  return false;
                }
                return true;
        }
    }
    return true;
}

// Runs just one time when the keyboard initializes.
void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
    rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

// Runs whenever there is a layer state change.
layer_state_t layer_state_set_user(layer_state_t state) {
    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();

    // Limit the indicator LED brightness.
    // Otherwise they are super bright.
    ergodox_led_all_set(10);

    uint8_t layer = get_highest_layer(state);
    switch (layer) {
        case 0:
#ifdef RGBLIGHT_COLOR_LAYER_0
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
            break;
        case 1:
            ergodox_right_led_1_on();
#ifdef RGBLIGHT_COLOR_LAYER_1
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
#endif
            break;
        case 2:
            ergodox_right_led_2_on();
#ifdef RGBLIGHT_COLOR_LAYER_2
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
#endif
            break;
        case 3:
            ergodox_right_led_3_on();
#ifdef RGBLIGHT_COLOR_LAYER_3
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
#endif
            break;
        case 4:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
#ifdef RGBLIGHT_COLOR_LAYER_4
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
#endif
            break;
        case 5:
            ergodox_right_led_1_on();
            ergodox_right_led_3_on();
#ifdef RGBLIGHT_COLOR_LAYER_5
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
#endif
            break;
        case 6:
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
#ifdef RGBLIGHT_COLOR_LAYER_6
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
#endif
            break;
        case 7:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
#ifdef RGBLIGHT_COLOR_LAYER_7
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_7);
#endif
            break;
        default:
            break;
    }

    return state;
};

