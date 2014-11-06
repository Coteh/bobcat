#pragma once
#include "Rect.h"
class CollisionMath {
public:
	static bool CheckIfCollided2D(Rect2D _r1, Rect2D _r2);
	static bool CheckIfCollided3D(Rect3D _r1, Rect3D _r2);
};

