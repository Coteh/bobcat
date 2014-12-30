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
	if (components.count(_index) > 0){
		return components.at(_index);
	}
	return nullptr;
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