#pragma once
#include "AbstractNotifier.h"

namespace InputEnums {
	/**
	* Enum for Input State.
	*/
	enum InputState {
		INPUT_NONE = 0x00, /**< Input is stationary */
		INPUT_PRESSED = 0x01, /**< Input is pressed */
		INPUT_HELD = 0x02, /**< Input is held down */
		INPUT_RELEASED = 0x04 /**< Input is released */
	};
	/**
	* Enum for KeyCode.
	*/
	enum KeyCode {
		KEY_UNKNOWN, KEY_UP, KEY_DOWN, KEY_RIGHT, KEY_LEFT, KEY_PAGE_UP, KEY_PAGE_DOWN,
		KEY_BACKSPACE, KEY_SPACE, KEY_ESCAPE, KEY_ENTER, KEY_0, KEY_1, KEY_2, KEY_3,
		KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_A, KEY_B, KEY_C, KEY_D, KEY_E,
		KEY_F, KEY_G, KEY_H, KEY_I, KEY_J, KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P,
		KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z, KEY_NUM0,
		KEY_NUM1, KEY_NUM2, KEY_NUM3, KEY_NUM4, KEY_NUM5, KEY_NUM6, KEY_NUM7, KEY_NUM8,
		KEY_NUM9
	};
}

namespace bobcat {

	/**
	* An abstract class that all Input Systems must derive from and use.
	* Input Systems have methods that allow for direct interfacing
	* with external input APIs.
	*/
	class AbstractInputSystem : public virtual AbstractNotifier {
	protected:
		/**
		* Translate InputSystem KeyCode to the equivalent
		* version from the input system being interfaced.
		* @param _keyCode KeyCode to translate.
		*/
		virtual int translateKeyCodeInput(int _keyCode) = 0;

		/**
		* Translate Input State outputted from the interfaced
		* system into an equivalent state from InputSystem.
		* @param _inputState Input State to translate.
		*/
		virtual int translateInputStateOutput(int _inputState) = 0;
	public:
		/**
		* Get the input state of the supplied KeyCode.
		* @param _keyCode KeyCode to get input state from.
		*/
		virtual int getInputState(int _keyCode) = 0;

		/**
		* Checks if there is a key pressed.
		* @note It's kind of a useless command right now though.
		*/
		virtual bool isKeyPressed() = 0;

		virtual ~AbstractInputSystem(){};
	};

}