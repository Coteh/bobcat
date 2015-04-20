#pragma once
#include "Component.h"
#include <glm\glm.hpp>

namespace bobcat {

	/**
	* Transform is a component that gives a GameObject a position, rotation, and scale that can be used
	* to represent the object within the game world.
	*/
	class Transform : public Component {
	private:
		glm::mat4 m_orientation;
		glm::vec3 m_position;
		glm::vec3 m_rotation;
		glm::vec3 m_scale;
		glm::vec3 m_forward;
		glm::vec3 m_up;
		glm::vec3 m_right;

		void determineDirections();
	public:
		Transform();
		virtual ~Transform();

		/**
		* Get the position of the GameObject.
		* @return Vector3 that represents the GameObject's position.
		* @note This is used in the position property and can also be called from there.
		*/
		glm::vec3 getPosition();

		/**
		* Get the rotation of the GameObject.
		* @return Vector3 that represents the GameObject's rotation.
		* @note This is used in the rotation property and can also be called from there.
		*/
		//glm::vec3 getRotation();

		/**
		* Get the scale of the GameObject.
		* @return Vector3 that represents the GameObject's scale.
		* @note This is used in the scale property and can also be called from there.
		*/
		glm::vec3 getScale();

		/**
		* Get the forward direction of the GameObject.
		* @return Vector3 that represents the GameObject's forward direction.
		* @note This is used in the forward property and can also be called from there.
		*/
		glm::vec3 getForward();

		/**
		* Get the up direction of the GameObject.
		* @return Vector3 that represents the GameObject's up direction.
		* @note This is used in the up property and can also be called from there.
		*/
		glm::vec3 getUp();

		/**
		* Get the right direction of the GameObject.
		* @return Vector3 that represents the GameObject's right direction.
		* @note This is used in the right property and can also be called from there.
		*/
		glm::vec3 getRight();

		glm::mat4 getOrientation();

		/**
		* Set the position of the GameObject.
		* @param _pos Vector3 that would represent the GameObject's position.
		* @note This is used in the position property and can also be called from there.
		*/
		void setPosition(glm::vec3 _pos);

		/**
		* Set the scale of the GameObject.
		* @param _sca Vector3 that would represent the GameObject's scale.
		* @note This is used in the scale property and can also be called from there.
		*/
		void setScale(glm::vec3 _sca);

		/**
		* Set the forward direction of the GameObject.
		* @param _fwd Vector3 that would represent the GameObject's forward direction.
		* @note This is used in the forward property and can also be called from there.
		*/
		void setForward(glm::vec3 _fwd);

		/**
		* Set the up direction of the GameObject.
		* @param _up Vector3 that would represent the GameObject's up direction.
		* @note This is used in the up property and can also be called from there.
		*/
		void setUp(glm::vec3 _up);

		/**
		* Set the right direction of the GameObject.
		* @param _rgt Vector3 that would represent the GameObject's right direction.
		* @note This is used in the right property and can also be called from there.
		*/
		void setRight(glm::vec3 _rgt);

		void Rotate(glm::vec3 _euler);

		void ResetOrientation();

		/**
		* Property to access the Transform position.
		*/
		__declspec(property(get = getPosition, put = setPosition)) glm::vec3 position;

		/**
		* Property to access the Transform rotation.
		*/
		/*__declspec(property(get = getRotation)) glm::vec3 rotation;*/

		/**
		* Property to access the Transform scale.
		*/
		__declspec(property(get = getScale, put = setScale)) glm::vec3 scale;

		/**
		* Property to access the Transform forward vector.
		*/
		__declspec(property(get = getForward, put = setForward)) glm::vec3 forward;

		/**
		* Property to access the Transform up vector.
		*/
		__declspec(property(get = getUp, put = setUp)) glm::vec3 up;

		/**
		* Property to access the Transform right vector.
		*/
		__declspec(property(get = getRight, put = setRight)) glm::vec3 right;

		__declspec(property(get = getOrientation)) glm::mat4 orientation;
	};

}