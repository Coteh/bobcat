#include "SFMLInputSystem.h"
#include <SFML\Window\Keyboard.hpp>

SFMLInputSystem* SFMLInputSystem::currSFMLInputSystem;

SFMLInputSystem::SFMLInputSystem(SFMLWindower* _sfmlWindower) {
	m_sfmlWindower = _sfmlWindower;
	currSFMLInputSystem = this;
	m_sfmlWindower->sfEventListener = SFMLEventHandler;
}

SFMLInputSystem::~SFMLInputSystem() {

}

bool SFMLInputSystem::isKeyPressed() {
	return false;
}

int SFMLInputSystem::translateKeyCodeInput(int _keyCode) {
	switch (_keyCode){
	case InputEnums::KeyCode::KEY_0:			return sf::Keyboard::Num0;
	case InputEnums::KeyCode::KEY_1:			return sf::Keyboard::Num1;
	case InputEnums::KeyCode::KEY_2:			return sf::Keyboard::Num2;
	case InputEnums::KeyCode::KEY_3:			return sf::Keyboard::Num3;
	case InputEnums::KeyCode::KEY_4:			return sf::Keyboard::Num4;
	case InputEnums::KeyCode::KEY_5:			return sf::Keyboard::Num5;
	case InputEnums::KeyCode::KEY_6:			return sf::Keyboard::Num6;
	case InputEnums::KeyCode::KEY_7:			return sf::Keyboard::Num7;
	case InputEnums::KeyCode::KEY_8:			return sf::Keyboard::Num8;
	case InputEnums::KeyCode::KEY_9:			return sf::Keyboard::Num9;
	case InputEnums::KeyCode::KEY_A:			return sf::Keyboard::A;
	case InputEnums::KeyCode::KEY_B:			return sf::Keyboard::B;
	case InputEnums::KeyCode::KEY_C:			return sf::Keyboard::C;
	case InputEnums::KeyCode::KEY_D:			return sf::Keyboard::D;
	case InputEnums::KeyCode::KEY_E:			return sf::Keyboard::E;
	case InputEnums::KeyCode::KEY_F:			return sf::Keyboard::F;
	case InputEnums::KeyCode::KEY_G:			return sf::Keyboard::G;
	case InputEnums::KeyCode::KEY_H:			return sf::Keyboard::H;
	case InputEnums::KeyCode::KEY_I:			return sf::Keyboard::I;
	case InputEnums::KeyCode::KEY_J:			return sf::Keyboard::J;
	case InputEnums::KeyCode::KEY_K:			return sf::Keyboard::K;
	case InputEnums::KeyCode::KEY_L:			return sf::Keyboard::L;
	case InputEnums::KeyCode::KEY_M:			return sf::Keyboard::M;
	case InputEnums::KeyCode::KEY_N:			return sf::Keyboard::N;
	case InputEnums::KeyCode::KEY_O:			return sf::Keyboard::O;
	case InputEnums::KeyCode::KEY_P:			return sf::Keyboard::P;
	case InputEnums::KeyCode::KEY_Q:			return sf::Keyboard::Q;
	case InputEnums::KeyCode::KEY_R:			return sf::Keyboard::R;
	case InputEnums::KeyCode::KEY_S:			return sf::Keyboard::S;
	case InputEnums::KeyCode::KEY_T:			return sf::Keyboard::T;
	case InputEnums::KeyCode::KEY_U:			return sf::Keyboard::U;
	case InputEnums::KeyCode::KEY_V:			return sf::Keyboard::V;
	case InputEnums::KeyCode::KEY_W:			return sf::Keyboard::W;
	case InputEnums::KeyCode::KEY_X:			return sf::Keyboard::X;
	case InputEnums::KeyCode::KEY_Y:			return sf::Keyboard::Y;
	case InputEnums::KeyCode::KEY_Z:			return sf::Keyboard::Z;
	case InputEnums::KeyCode::KEY_UP:			return sf::Keyboard::Up;
	case InputEnums::KeyCode::KEY_DOWN:			return sf::Keyboard::Down;
	case InputEnums::KeyCode::KEY_RIGHT:		return sf::Keyboard::Right;
	case InputEnums::KeyCode::KEY_LEFT:			return sf::Keyboard::Left;
	case InputEnums::KeyCode::KEY_PAGE_UP:		return sf::Keyboard::PageUp;
	case InputEnums::KeyCode::KEY_PAGE_DOWN:	return sf::Keyboard::PageDown;
	case InputEnums::KeyCode::KEY_BACKSPACE:	return sf::Keyboard::BackSpace;
	case InputEnums::KeyCode::KEY_SPACE:		return sf::Keyboard::Space;
	case InputEnums::KeyCode::KEY_ESCAPE:		return sf::Keyboard::Escape;
	case InputEnums::KeyCode::KEY_ENTER:		return sf::Keyboard::Return;
	}
	return sf::Keyboard::Unknown;
}

int SFMLInputSystem::translateInputStateOutput(int _inputState) {
	int currState = -1;
	switch (_inputState) {
	case 0:
		currState = InputEnums::InputState::INPUT_RELEASED;
		break;
	case 1:
		currState = InputEnums::InputState::INPUT_PRESSED;
		break;
	default:
		currState = InputEnums::InputState::INPUT_NONE;
		break;
	}
	m_prevState = currState;
	return currState;
}

int SFMLInputSystem::getInputState(int _keyCode) {
	sf::Keyboard::Key keyCode = (sf::Keyboard::Key)translateKeyCodeInput(_keyCode);
	return translateInputStateOutput(sf::Keyboard::isKeyPressed(keyCode));
}

void SFMLInputSystem::handleEvent(sf::Event _evt) {
	if (_evt.type == sf::Event::KeyPressed || _evt.type == sf::Event::KeyReleased) {
		notifyObservers();
	}
}

void SFMLInputSystem::SFMLEventHandler(sf::Event _evt) {
	if (currSFMLInputSystem != nullptr){
		currSFMLInputSystem->handleEvent(_evt);
	}
}