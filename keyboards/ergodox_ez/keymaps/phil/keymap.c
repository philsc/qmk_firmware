#include QMK_KEYBOARD_H
#define QMK_KEYS_PER_SCAN 8
#include "action_layer.h"
#include "debug.h"
#include "keymap_introspection.h"
#include "raw_hid.h"
#include "version.h"

enum layers {
    BASE,  // default layer
    GAME,  // gaming keys
    MDIA,  // media keys
    SYMB,  // symbols
};

enum custom_keycodes {
  VRSN = SAFE_RANGE,  // can always be here
  CUSTOM_KEYCODE_END,  // keep last; sizes user_keycode_names below
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
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------| Home |ScrlUp|ScrlDn| End  |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Mclk | Lclk |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 | Rclk |      |------|       |------| PgDn |Back  |
 *                                 |      |      |      |       | PgUp |      |      |
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
                 KC_HOME, KC_WH_D, KC_WH_U, KC_END,  KC_TRNS, KC_MPLY,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
                          KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_PGUP, KC_PGDN, KC_WBAK
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

// Keymap dump over raw HID.
//
// The desktop asks the keyboard for its keymap so that whatever is shown always
// matches the firmware that is flashed. Every packet is RAW_EPSIZE bytes; the
// reply echoes the request's command byte, or KD_ERROR with the reason.
//
//   KD_INFO        [01]                   -> [01 proto rows cols layers 'K' 'M' 'P' n_user]
//   KD_KEYCODES    [02 layer start count] -> [02 layer start count kc_lo kc_hi ...]
//                                            (start/count index row * MATRIX_COLS + col)
//   KD_LAYER_NAME  [03 layer]             -> [03 layer name...]
//   KD_STATE       [04]                   -> [04 layer_state(4) default_layer_state(4) highest]
//   KD_USER_NAME   [05 n]                 -> [05 n name...]   (name of SAFE_RANGE + n)
//   anything else                         -> [FF cmd err]
enum keymap_dump_command {
    KD_INFO       = 0x01,
    KD_KEYCODES   = 0x02,
    KD_LAYER_NAME = 0x03,
    KD_STATE      = 0x04,
    KD_USER_NAME  = 0x05,
    KD_ERROR      = 0xFF,
};

enum keymap_dump_error {
    KD_ERR_UNKNOWN_CMD = 1,
    KD_ERR_BAD_ARG     = 2,
};

#define KD_PROTOCOL 1
#define KD_NAME_LEN 8
#define KD_MAX_KEYCODES ((RAW_EPSIZE - 4) / 2)

// The names must follow the enums above; the asserts keep them in sync.
static const char PROGMEM layer_names[][KD_NAME_LEN] = {
    [BASE] = "BASE",
    [GAME] = "GAME",
    [MDIA] = "MDIA",
    [SYMB] = "SYMB",
};
_Static_assert(ARRAY_SIZE(layer_names) == ARRAY_SIZE(keymaps), "name every layer");

static const char PROGMEM user_keycode_names[][KD_NAME_LEN] = {
    [VRSN - SAFE_RANGE] = "VRSN",
};
_Static_assert(ARRAY_SIZE(user_keycode_names) == CUSTOM_KEYCODE_END - SAFE_RANGE, "name every custom keycode");

static void kd_put_u32(uint8_t *p, uint32_t v) {
    p[0] = v;
    p[1] = v >> 8;
    p[2] = v >> 16;
    p[3] = v >> 24;
}

// Fills resp (zeroed, resp[0] already echoes the command) for the request in
// req. Returns 0 or a keymap_dump_error.
static uint8_t keymap_dump_handle(const uint8_t *req, uint8_t *resp) {
    switch (req[0]) {
        case KD_INFO:
            resp[1] = KD_PROTOCOL;
            resp[2] = MATRIX_ROWS;
            resp[3] = MATRIX_COLS;
            resp[4] = keymap_layer_count();
            resp[5] = 'K';
            resp[6] = 'M';
            resp[7] = 'P';
            resp[8] = ARRAY_SIZE(user_keycode_names);
            return 0;

        case KD_KEYCODES: {
            uint8_t layer = req[1];
            uint8_t start = req[2];
            uint8_t count = req[3];
            if (layer >= keymap_layer_count() || count > KD_MAX_KEYCODES || (uint16_t)start + count > MATRIX_ROWS * MATRIX_COLS) {
                return KD_ERR_BAD_ARG;
            }
            resp[1] = layer;
            resp[2] = start;
            resp[3] = count;
            for (uint8_t i = 0; i < count; i++) {
                uint8_t  idx = start + i;
                uint16_t kc  = keycode_at_keymap_location(layer, idx / MATRIX_COLS, idx % MATRIX_COLS);
                resp[4 + 2 * i] = kc & 0xFF;
                resp[5 + 2 * i] = kc >> 8;
            }
            return 0;
        }

        case KD_LAYER_NAME:
            if (req[1] >= ARRAY_SIZE(layer_names)) {
                return KD_ERR_BAD_ARG;
            }
            resp[1] = req[1];
            memcpy_P(&resp[2], layer_names[req[1]], KD_NAME_LEN);
            return 0;

        case KD_STATE:
            kd_put_u32(&resp[1], layer_state);
            kd_put_u32(&resp[5], default_layer_state);
            resp[9] = get_highest_layer(layer_state);
            return 0;

        case KD_USER_NAME:
            if (req[1] >= ARRAY_SIZE(user_keycode_names)) {
                return KD_ERR_BAD_ARG;
            }
            resp[1] = req[1];
            memcpy_P(&resp[2], user_keycode_names[req[1]], KD_NAME_LEN);
            return 0;
    }
    return KD_ERR_UNKNOWN_CMD;
}

void raw_hid_receive(uint8_t *data, uint8_t length) {
    uint8_t resp[RAW_EPSIZE] = {0};
    resp[0]     = data[0];
    uint8_t err = keymap_dump_handle(data, resp);
    if (err != 0) {
        memset(resp, 0, sizeof(resp));
        resp[0] = KD_ERROR;
        resp[1] = data[0];
        resp[2] = err;
    }
    // raw_hid_send requires exactly RAW_EPSIZE bytes.
    raw_hid_send(resp, sizeof(resp));
}

// Set when we bypassed the layer-tap and registered KC_SCLN ourselves, so
// that the release unregisters it again.
static bool scln_registered_as_key = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case VRSN:
            if (record->event.pressed) {
                SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION " built " QMK_BUILDDATE);
                return false;
            }
            break;
        case LT(MDIA, KC_SCLN):
            if (record->event.pressed) {
                // If the user is holding a modifier key, then we don't want to
                // switch layers.
                if ((get_mods() & (MOD_MASK_CTRL | MOD_MASK_SHIFT)) != 0) {
                    register_code(KC_SCLN);
                    scln_registered_as_key = true;
                    return false;
                }
            } else if (scln_registered_as_key) {
                // The press never went through the layer-tap logic, so the
                // release must not either. Otherwise KC_SCLN stays held.
                unregister_code(KC_SCLN);
                scln_registered_as_key = false;
                return false;
            }
            break;
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

