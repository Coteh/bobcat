#pragma once
#include <string>

class GameObject;

class Component {
private:
	GameObject* m_gameObject;
public:
	Component(){}
	~Component(){}

	GameObject* getGameObject(){
		return m_gameObject;
	}

	void setGameObject(GameObject* _gameObject){
		m_gameObject = _gameObject;
	}

	__declspec(property(get = getGameObject, put = setGameObject)) GameObject* gameObject;

	virtual void Update(float _deltaTime){}
};