#pragma once
#include <map>
#include "Component.h"

typedef std::map<std::string, Component*> ComponentMap;

class ComponentHolder {
	friend class GameObject;
private:
	ComponentMap components;
	ComponentMap::iterator getBegin();
	ComponentMap::iterator getEnd();
public:
	ComponentHolder();
	~ComponentHolder();

	void AddComponent(Component* _component);

	Component* GetComponent(std::string _name);
};

