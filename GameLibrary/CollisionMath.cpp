#include "CollisionMath.h"


bool CollisionMath::CheckIfCollided2D(Rect2D _r1, Rect2D _r2){
	return (_r1.x >= _r2.x && _r1.x + _r1.width <= _r2.x + _r2.width
		&& _r1.y >= _r2.y && _r1.y + _r1.height <= _r2.y + _r2.height);
}

bool CollisionMath::CheckIfCollided3D(Rect3D _r1, Rect3D _r2){
	return (CheckIfCollided2D(_r1, _r2) && _r1.z >= _r2.z && _r1.z + _r1.length <= _r2.z + _r2.length);
}
