#include "ComponentHolder.h"

ComponentHolder::ComponentHolder() {
}

ComponentHolder::~ComponentHolder() {
	//Wipes out component map from memory
	components.clear();
	ComponentMap clearMap;
	clearMap.swap(components);
}

void ComponentHolder::AddComponent(Component* _component){
	components[_component->name] = _component;
}

Component* ComponentHolder::GetComponent(std::string _name){
	return components[_name];
}

ComponentMap::iterator ComponentHolder::getBegin() {
	return components.begin();
}

ComponentMap::iterator ComponentHolder::getEnd() {
	return components.end();
}