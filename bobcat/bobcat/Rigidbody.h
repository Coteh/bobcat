#pragma once
#include "Component.h"
#include <glm\glm.hpp>

namespace bobcat {

	class Rigidbody : public Component {
	private:
		glm::vec3 m_velocity;
		glm::vec3 m_rotationalVel;
		glm::vec3 m_force;
		float m_friction;
	public:
		Rigidbody();
		virtual ~Rigidbody();

		glm::vec3 getVelocity();
		glm::vec3 getRotationalVel();
		glm::vec3 getForce();
		float getFriction();

		void setVelocity(glm::vec3 _vel);
		void setRotationalVel(glm::vec3 _rotVel);
		void setForce(glm::vec3 _force);
		void setFriction(float _fric);

		__declspec(property(get = getVelocity, put = setVelocity)) glm::vec3 velocity;
		__declspec(property(get = getRotationalVel, put = setRotationalVel)) glm::vec3 rotationalVel;
		__declspec(property(get = getForce, put = setForce)) glm::vec3 force;
		__declspec(property(get = getFriction, put = setFriction)) float friction;

		virtual void Update(float _deltaTime);
	};

}