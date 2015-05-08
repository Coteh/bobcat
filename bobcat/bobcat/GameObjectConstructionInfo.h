#pragma once
#include <glm\glm.hpp>
#include "Mesh.h"
#include "Collider.h"

namespace bobcat {

	/**
	* Information that can be applied to a new GameObject using GameObjectCreator.
	*/
	struct GameObjectConstructionInfo {
		friend class GameObjectCreator;
	private:
		bool isTransformSet = false;
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;

		ColliderType colliderType;

		bool isRigidbodySet = false;
		glm::vec3 velocity;
		glm::vec3 rotationalVel;
		float friction;

		Mesh* mesh;
	public:
		/**
		* Default constructor.
		*/
		GameObjectConstructionInfo(){
			mesh = nullptr;
		}

		/**
		* Set transform values that would be applied to a GameObject.
		* If this method is called, a Transform component will be added to every GameObject
		* that is created using information from this GameObjectConstructionInfo instance.
		* @param _pos Initial position.
		* @param _rot Initial rotation.
		* @param _scl Initial scale.
		*/
		inline void setTransformValues(glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scl){
			position = _pos;
			rotation = _rot;
			scale = _scl;
			isTransformSet = true;
		}

		/**
		* Set default transform values for a GameObject.
		* Will give the GameObject a Transform component upon creation.
		*/
		inline void setTransformValues(){
			setTransformValues(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f));
		}

		/**
		* Set the type of Collider GameObjects created with this information will have.
		* @param _mode The Collider type enum.
		*/
		inline void setColliderType(ColliderType _type){
			colliderType = _type;
		}

		/**
		* Set rigidbody values that would be applied to a GameObject.
		* If this method is called, a Rigidbody component will be added to every GameObject
		* that is created using information from this GameObjectConstructionInfo instance.
		* @param _velocity Initial velocity.
		* @param _rotationalVel Initial rotational velocity.
		* @param _friction Initial friction.
		*/
		inline void setRigidbodyValues(glm::vec3 _velocity, glm::vec3 _rotationalVel, float _friction){
			velocity = _velocity;
			rotationalVel = _rotationalVel;
			friction = _friction;
			isRigidbodySet = true;
		}

		/**
		* Set default rigidbody values for a GameObject.
		* Will give the GameObject a Rigidbody component upon creation.
		*/
		inline void setRigidbodyValues(){
			setRigidbodyValues(glm::vec3(0.0f), glm::vec3(0.0f), 1.0f);
		}

		/**
		* Provide the Mesh that all GameObjects created with this information will have.
		* @param _mesh The Mesh to provide.
		*/
		inline void setMesh(Mesh* _mesh){
			mesh = _mesh;
		}

		~GameObjectConstructionInfo(){}
	};

}