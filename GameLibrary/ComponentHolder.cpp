#include "ComponentHolder.h"

ComponentHolder::ComponentHolder() {
}

ComponentHolder::~ComponentHolder() {
	RemoveAll();
}

void ComponentHolder::AddComponent(Component* _component, std::type_index _index){
	components[_index] = _component;
}

Component* ComponentHolder::GetComponent(std::type_index _index){
	return components[_index];
}

ComponentMap::iterator ComponentHolder::getBegin() {
	return components.begin();
}

ComponentMap::iterator ComponentHolder::getEnd() {
	return components.end();
}

void ComponentHolder::RemoveComponent(std::type_index _index){
	components.erase(_index);
}

void ComponentHolder::RemoveAll(){
	//Wipe out component map data from memory
	components.clear();
	ComponentMap clearMap;
	clearMap.swap(components);
}