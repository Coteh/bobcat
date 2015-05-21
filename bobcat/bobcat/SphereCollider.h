#pragma once
#include "Collider.h"

namespace bobcat {

	class SphereCollider : public Collider {
	public:
		SphereCollider();
		virtual ~SphereCollider();
		virtual float getRadius();
		virtual glm::vec3 getDimensions();
		virtual void setRadius(float _radius);
	private:
		float m_radius;
	};

}