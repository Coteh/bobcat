#pragma once

#include <map>
#include <typeindex>
#include <glm\glm.hpp>
#include "Component.h"
#include "Mesh.h"
#include "TextureLoader.h"

#include "Transform.h"
#include "Collider.h"
#include "Rigidbody.h"
#include "MeshRenderer.h"

#include "ComponentHolder.h"

namespace bobcat {

	enum RELATIVE_TO {
		PARENT = 0,
		WORLD = 1
	};

	/**
	* A GameObject is an entity in a scene.
	*/
	class GameObject {
	private:
		GameObject* m_parent;
		std::vector<GameObject*> children;
		std::string name;
		ComponentHolder* componentHolder;

		void AddComponent(Component* _component, std::type_index _index);
	public:
		GameObject();

		~GameObject();

		/**
		* Get a list of this GameObject's children.
		* @return A STL vector containing a collection of child GameObject references.
		*/
		std::vector<GameObject*> getChildren();

		/**
		* Get the GameObject's name.
		* @return A STL string containing the GameObject's name.
		*/
		std::string getName();

		/**
		* Get the Model Matrix for this GameObject.
		* @return A Matrix4x4 of the Model Matrix.
		*/
		glm::mat4 getModelMat();

		GameObject* getParent();

		/**
		* Set a name for this GameObject.
		* @param _name Name to give to the GameObject.
		*/
		void setName(std::string _name);

		/**
		* Attach a GameObject to this GameObject as a child.
		* @param _gameObject GameObject to attach.
		*/
		void attachGameObject(GameObject* _gameObject);

		void setParent(GameObject* _parent);

		/**
		* Add a Component of a particular Component type to this GameObject.
		* @tparam T Type of Component to add.
		*/
		template <typename T>
		T* AddComponent();

		/**
		* Get a Component of a particular Component type from this GameObject.
		* @tparam T Type of Component to retrieve.
		* @return T type Component.
		*/
		template <typename T>
		T* GetComponent();

		/**
		* Remove a Component of a particular Component type from this GameObject.
		* @tparam T Type of Component to remove.
		*/
		template <typename T>
		void RemoveComponent();

		/**
		* Remove all Components from this GameObject.
		*/
		void RemoveAllComponents();

		/**
		* Update the GameObject.
		* @param deltaTime Delta Time from the game engine.
		*/
		void Update(float _deltaTime);

		/**
		* Call GameObject drawing methods.
		*/
		void Draw();

		Transform* transform; /**< Public reference to Transform component if it exists. */
		Collider* collider; /**< Public reference to Collider component if it exists. */
		Rigidbody* rigidbody; /**< Public reference to Rigidbody component if it exists. */
		MeshRenderer* renderer; /**< Public reference to MeshRenderer component if it exists. */

		__declspec(property(get = getParent, put = setParent)) GameObject* parent;

		bool isWireFrameOn; /**< Set GameObject wireframe on/off. */
		RELATIVE_TO relativeTo;
	};

	template <typename T>
	T* GameObject::AddComponent() {
		//static_assert(std::is_base_of<Component, T>(), "This is not a component, cannot add it to GameObject");
		T* com = new T();
		std::type_index index(typeid(com));
		AddComponent(com, typeid(com));
		return com;
	}

	template <typename T>
	T* GameObject::GetComponent() {
		if (componentHolder == nullptr) return nullptr;
		return (T*)componentHolder->GetComponent(typeid(T*));
	}

	template <typename T>
	void GameObject::RemoveComponent() {
		if (componentHolder == nullptr) return;
		componentHolder->RemoveComponent(typeid(T*));
	}

}