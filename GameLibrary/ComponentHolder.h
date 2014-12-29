#pragma once
#include <typeindex>
#include <map>
#include "Component.h"

typedef std::map<std::type_index, Component*> ComponentMap;

class ComponentHolder {
	friend class GameObject;
private:
	ComponentMap components;
public:
	ComponentHolder();
	~ComponentHolder();

	void AddComponent(Component* _component, std::type_index _index);

	Component* GetComponent(std::type_index _index);

	void RemoveComponent(std::type_index _index);
	void RemoveAll();

	ComponentMap::iterator getBegin();
	ComponentMap::iterator getEnd();
};

