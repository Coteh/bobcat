#pragma once
#include "AbstractNotifier.h"

namespace InputEnums {
	enum InputState {
		INPUT_NONE = 0x00,
		INPUT_PRESSED = 0x01,
		INPUT_HELD = 0x02,
		INPUT_RELEASED = 0x04
	};
	enum KeyCode {
		KEY_UNKNOWN, KEY_UP, KEY_DOWN, KEY_RIGHT, KEY_LEFT, KEY_PAGE_UP, KEY_PAGE_DOWN,
		KEY_BACKSPACE, KEY_SPACE, KEY_ESCAPE, KEY_ENTER, KEY_0, KEY_1, KEY_2, KEY_3,
		KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_A, KEY_B, KEY_C, KEY_D, KEY_E,
		KEY_F, KEY_G, KEY_H, KEY_I, KEY_J, KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P,
		KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z
	};
}

class AbstractInputSystem : public virtual AbstractNotifier {
protected:
	virtual int translateKeyCodeInput(int _keyCode) = 0;
	virtual int translateInputStateOutput(int _inputState) = 0;
public:
	virtual int getInputState(int _keyCode) = 0;

	virtual bool isKeyPressed() = 0;

	virtual ~AbstractInputSystem(){};
};