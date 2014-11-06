#pragma once

struct Rect2D{
	float x, y, height, width;
};

struct Rect3D : Rect2D{
	float z, length;
};