#pragma once
#include <typeindex>
#include <map>
#include "Component.h"

namespace bobcat {

	typedef std::map<std::type_index, Component*> ComponentMap;

	/**
	* A container that holds Components for a GameObject.
	*/
	class ComponentHolder {
		friend class GameObject;
	private:
		ComponentMap components;
	public:
		ComponentHolder();
		~ComponentHolder();

		/**
		* Add a Component to the ComponentHolder.
		* @param _component Component to be added.
		* @param _index The type of Component being added.
		*/
		void AddComponent(Component* _component, std::type_index _index);

		/**
		* Get a Component from the ComponentHolder.
		* @param _index The type of Component to return.
		*/
		Component* GetComponent(std::type_index _index);

		/**
		* Remove a Component from the ComponentHolder.
		* @param _index The type of Component to remove.
		*/
		void RemoveComponent(std::type_index _index);

		/**
		* Remove all Components from a ComponentHolder.
		*/
		void RemoveAll();

		/**
		* Get the beginning iterator of the ComponentHolder.
		*/
		ComponentMap::iterator getBegin();

		/**
		* Get the ending iterator of the ComponentHolder.
		*/
		ComponentMap::iterator getEnd();
	};

}