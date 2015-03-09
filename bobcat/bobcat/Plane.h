#pragma once
#include <glm/glm.hpp>

namespace bobcat {

	class Plane {
	private:
		glm::vec3 point;
		float a, b, c, d;
	public:
		Plane() : a(0.0f), b(1.0f), c(0.0f), d(0.0f), point(glm::vec3(0.0f)){}

		Plane(float _a, float _b, float _c, float _d, glm::vec3 _point) : a(_a), b(_b), c(_c), d(_d), point(_point){}

		~Plane();


	};

}