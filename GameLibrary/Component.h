#pragma once
#include <string>

namespace bobcat {

	class GameObject;

	/**
	* A Component provides additional functionality to a GameObject that can be hotswapped in and out.
	*/
	class Component {
	private:
		GameObject* m_gameObject;
	public:
		Component(){}
		~Component(){}

		/**
		* Returns the GameObject this component is attached to.
		* @note This is used in the gameObject property and can also be called from there.
		*/
		GameObject* getGameObject(){
			return m_gameObject;
		}

		/**
		* Sets the GameObject to be referenced by the Component
		* @note It currently does not change which GameObject has it attached.
		* @note This is used in the gameObject property and can also be called from there.
		*/
		void setGameObject(GameObject* _gameObject){
			m_gameObject = _gameObject;
		}

		/**
		* Property to access the GameObject referenced by the Component.
		*/
		__declspec(property(get = getGameObject, put = setGameObject)) GameObject* gameObject;

		/**
		* Update the Component.
		* @param deltaTime Delta Time from the game engine.
		*/
		virtual void Update(float _deltaTime){}
	};

}