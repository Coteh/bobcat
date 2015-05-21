#include "Component.h"
#include "GameObject.h"

using namespace bobcat;

GameObject* Component::getGameObject(){
	return m_gameObject;
}

Transform* Component::getTransform(){
	if (m_gameObject == nullptr) return nullptr;
	return m_gameObject->transform;
}

void Component::setGameObject(GameObject* _gameObject){
	m_gameObject = _gameObject;
}