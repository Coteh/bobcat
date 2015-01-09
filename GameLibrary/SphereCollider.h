#pragma once
#include "Collider.h"

namespace bobcat {

	class SphereCollider : public Collider {
	private:
		float m_radius;
	public:
		SphereCollider();
		~SphereCollider();
		virtual float getRadius();
		virtual glm::vec3 getDimensions();
		virtual void setRadius(float _radius);
	};

}