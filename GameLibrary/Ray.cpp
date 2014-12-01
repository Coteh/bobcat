#include "Ray.h"

bool Ray::intersects(glm::vec3 _pos, float _radius, float *_dist){
	glm::vec3 rayToSphereDir;
	float rayToSphereLength = 0.0f;
	float intersectPoint = 0.0f;
	float squaredPoint = 0.0f;

	rayToSphereDir = _pos - origin;
	rayToSphereLength = glm::dot(rayToSphereDir, rayToSphereDir);

	intersectPoint = glm::dot(rayToSphereDir, direction);

	if (intersectPoint < 0){
		return false;
	}

	squaredPoint = (_radius * _radius) - rayToSphereLength + (intersectPoint * intersectPoint);

	if (squaredPoint < 0){
		return false;
	}

	if (_dist){
		*_dist = intersectPoint - (float)sqrt(squaredPoint);
	}

	return true;
}