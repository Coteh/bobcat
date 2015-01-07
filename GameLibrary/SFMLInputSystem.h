#pragma once
#include "AbstractInputSystem.h"
#include "SFMLWindower.h"
#include "Notifier.h"

/**
* The SFML implementation of AbstractInputSystem.
* It is used to interface directly with the input portion of the SFML windowing system.
*/
class SFMLInputSystem : public AbstractInputSystem, public Notifier {
private:
	SFMLWindower* m_sfmlWindower;
	int m_prevState;

	static SFMLInputSystem* currSFMLInputSystem;
protected:
	virtual int translateKeyCodeInput(int _keyCode);
	virtual int translateInputStateOutput(int _inputState);
public:
	/**
	* Default constructor for SFMLInputSystem.
	* Provide a pointer to SFMLWindower that this input system can use.
	* @note The SFMLWindower instance is used to listen to events being polled from the SFML window.
	*/
	SFMLInputSystem(SFMLWindower* _sfmlWindower);
	
	/**
	* Handles a SFML event callback.
	*/
	void handleEvent(sf::Event _evt);

	/**
	* Static SFML Event Handling callback.
	* @param _evt SFML event received.
	*/
	static void SFMLEventHandler(sf::Event _evt);

	virtual int getInputState(int _keyCode);

	virtual bool isKeyPressed();

	virtual ~SFMLInputSystem();
};

