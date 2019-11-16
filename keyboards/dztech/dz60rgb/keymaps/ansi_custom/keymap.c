#include QMK_KEYBOARD_H

enum dz60rgb_layers {
	_QWERTY,
	_FN1,
	_RGB
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_QWERTY] = LAYOUT_60_ansi( /* Base */
		KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,  KC_BSPC,\
		KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC, KC_BSLASH,\
		KC_LCTL,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,           KC_ENT, \
		KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,                     KC_RSFT,\
		MO(_FN1), KC_LALT,  KC_LGUI,                      KC_SPC,                                 KC_RALT,  MO(_RGB), MO(_FN1),          KC_RCTL),
	[_FN1] = LAYOUT_60_ansi( /* FN1 */
		KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DEL ,\
		_______,  _______,  KC_UP,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RESET  ,\
		_______,  KC_LEFT,  KC_DOWN,  KC_RIGHT, _______,  _______,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RIGHT, _______,  _______,            _______,\
		_______,  _______,  _______,  _______,  _______,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_MPRV,  KC_MNXT,  KC_MPLY,                      _______,\
		_______,  _______,  _______,                      _______,                                _______,  _______,  _______,            _______),
	[_RGB] = LAYOUT_60_ansi( /* FN2 */
		KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DEL ,\
		_______,  RGB_TOG,  _______,  RGB_HUI,  RGB_HUD,  RGB_SAI,  RGB_SAD,  RGB_VAI,  RGB_VAD,  RGB_MOD,  _______,  _______,  _______,  RESET  ,\
		_______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_SPI,  RGB_SPD,  _______,  _______,            _______,\
		_______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,\
		_______,  _______,  _______,                      _______,                                _______,  _______,  _______,            _______),
	};

/*
#define LAYOUT_60_ansi( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B,      K2D, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B,           \
    K40, K41, K42,           K45,                K49, K4A, K4B,      K4D  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, XXX, K2D }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, XXX, XXX }, \
    { K40, K41, K42, XXX, XXX, K45, XXX, XXX, XXX, K49, K4A, K4B, XXX, K4D }  \
}
		{  13,  12,  11,  10,   9,   8,   7,   6,   5,   4,   3,   2,   1,   0 },
		{  27,  26,  25,  24,  23,  22,  21,  20,  19,  18,  17,  16,  15,  14 },
		{  40,  39,  38,  37,  36,  35,  34,  33,  32,  31,  30,  29, NO_LED,  28 },
		{  52,  51,  50,  49,  48,  47,  46,  45,  44,  43,  42,  41, NO_LED, NO_LED },
		{  60,  59,  58, NO_LED, NO_LED,  57, NO_LED, NO_LED, NO_LED,  56,  55,  54, NO_LED,  53 }
*/

void rgb_matrix_layer_helper (uint8_t red, uint8_t green, uint8_t blue, bool default_layer) {
	for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
		if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_MODIFIER)) {
			rgb_matrix_set_color( i, red, green, blue );
		}
	}
}

void rgb_matrix_indicators_user(void) {
	uint8_t this_led = host_keyboard_leds();
	if (!g_suspend_state && rgb_matrix_config.enable) {
		switch (biton32(layer_state)) {
			case _QWERTY:
				break;
			case _FN1:
				// WASD
				rgb_matrix_set_color(25, 0xFF, 0x00, 0x00);
				rgb_matrix_set_color(39, 0xFF, 0x00, 0x00);
				rgb_matrix_set_color(38, 0xFF, 0x00, 0x00);
				rgb_matrix_set_color(37, 0xFF, 0x00, 0x00);
				// HJKL
				rgb_matrix_set_color(34, 0xFF, 0x00, 0x00);
				rgb_matrix_set_color(33, 0xFF, 0x00, 0x00);
				rgb_matrix_set_color(32, 0xFF, 0x00, 0x00);
				rgb_matrix_set_color(31, 0xFF, 0x00, 0x00);
				// Media / Volume
				rgb_matrix_set_color(42, 0xFF, 0x00, 0x00);
				rgb_matrix_set_color(43, 0xFF, 0x00, 0x00);
				rgb_matrix_set_color(44, 0xFF, 0x00, 0x00);
				rgb_matrix_set_color(45, 0xFF, 0x00, 0x00);
				rgb_matrix_set_color(46, 0xFF, 0x00, 0x00);
				rgb_matrix_set_color(47, 0xFF, 0x00, 0x00);

				break;
			case _RGB: {
				HSV hsv = { rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, rgb_matrix_config.hsv.v };
				HSV hui = hsv;
				HSV hud = hsv;
				HSV sai = hsv;
				HSV sad = hsv;
				HSV vai = hsv;
				HSV vad = hsv;

				hui.h = hsv.h + 20;
				hud.h = hsv.h - 20;

				sai.s = 255 - hsv.s;
				sad.s = 255 - hsv.s;
				sai.s = sai.s + 16 > 255 ? 255 : sai.s + 16;
				sad.s = sad.s - 16 < 0   ?   0 : sad.s - 16;

				vai.v = 255 - hsv.v;
				vad.v = 255 - hsv.v;
				vai.v = vai.v + 16 > 255 ? 255 : vai.v + 16;
				vad.v = vad.v - 16 < 0   ?   0 : vad.v - 16;

				RGB rgbHUI = hsv_to_rgb(hui);
				RGB rgbHUD = hsv_to_rgb(hud);
				RGB rgbSAI = hsv_to_rgb(sai);
				RGB rgbSAD = hsv_to_rgb(sad);
				RGB rgbVAI = hsv_to_rgb(vai);
				RGB rgbVAD = hsv_to_rgb(vad);

				rgb_matrix_set_color(26, 0xFF, 0x80, 0x00); //ON
				rgb_matrix_set_color(19, 0xFF, 0x80, 0x00); //MOD
				rgb_matrix_set_color(24, rgbHUI.r, rgbHUI.g, rgbHUI.b); //HUI
				rgb_matrix_set_color(23, rgbHUD.r, rgbHUD.g, rgbHUD.b); //HUD
				rgb_matrix_set_color(22, rgbSAI.r, rgbSAI.g, rgbSAI.b); //SAI
				rgb_matrix_set_color(21, rgbSAD.r, rgbSAD.g, rgbSAD.b); //SAD
				rgb_matrix_set_color(20, rgbVAI.r, rgbVAI.g, rgbVAI.b); //VAI
				rgb_matrix_set_color(19, rgbVAD.r, rgbVAD.g, rgbVAD.b); //VAD

				break;
			}
		}
	}
	if ( this_led & (1<<USB_LED_CAPS_LOCK)) {
		rgb_matrix_set_color(40, 0xFF, 0xFF, 0xFF);
	}
}

void matrix_init_user(void) {
	//user initialization
}

void matrix_scan_user(void) {
	//user matrix
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	return true;
}
