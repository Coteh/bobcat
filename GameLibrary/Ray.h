#pragma once
#include <glm/glm.hpp>

namespace bobcat {

	class Ray {
	private:
		glm::vec3 origin;
		glm::vec3 direction;
	public:
		Ray(glm::vec3 _origin, glm::vec3 _direction) : origin(_origin), direction(_direction){}
		~Ray(){}

		void updateRay(glm::vec3 _origin, glm::vec3 _direction){
			origin = _origin;
			direction = _direction;
		}

		bool intersects(glm::vec3 _pos, float _radius, float *_dist);
	};

}