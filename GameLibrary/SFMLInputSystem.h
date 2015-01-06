#pragma once
#include "AbstractInputSystem.h"
#include "SFMLWindower.h"
#include "Notifier.h"

class SFMLInputSystem : public AbstractInputSystem, public Notifier {
private:
	SFMLWindower* m_sfmlWindower;
	int m_prevState;

	static SFMLInputSystem* currSFMLInputSystem;
protected:
	virtual int translateKeyCodeInput(int _keyCode);
	virtual int translateInputStateOutput(int _inputState);
public:
	SFMLInputSystem(SFMLWindower* _sfmlWindower);
	virtual ~SFMLInputSystem();

	virtual int getInputState(int _keyCode);

	void handleEvent(sf::Event _evt);

	virtual bool isKeyPressed();

	static void SFMLEventHandler(sf::Event _evt);
};

