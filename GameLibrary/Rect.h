#pragma once
#include <glm\glm.hpp>

struct Rect2D{
	float x, y, height, width;
	inline void Load(float _x, float _y, float _width, float _height){
		x = _x;
		y = _y;
		width = _width;
		height = _height;
	}
	inline Rect2D(){
		Load(0.0f, 0.0f, 0.0f, 0.0f);
	}
	inline Rect2D(float _x, float _y, float _width, float _height){
		Load(_x, _y, _width, _height);
	}
	inline Rect2D(glm::vec2 _pos, glm::vec2 _size){
		Load(_pos.x, _pos.y, _size.x, _size.y);
	}
	inline Rect2D(glm::vec2 _pos, float _width, float _height){
		Load(_pos.x, _pos.y, _width, _height);
	}
};

struct Rect3D : Rect2D{
	float z, length;
	inline void Load(float _x, float _y, float _z, float _width, float _height, float _length){
		Rect2D::Load(_x, _y, _width, _height);
		z = _z;
		length = _length;
	}
	inline Rect3D(){
		Load(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	}
	inline Rect3D(float _x, float _y, float _z, float _width, float _height, float _length){
		Load(_x, _y, _z, _width, _height, _length);
	}
	inline Rect3D(glm::vec3 _pos, glm::vec3 _size){
		Load(_pos.x, _pos.y, _pos.z, _size.x, _size.y, _size.z);
	}
	inline Rect3D(glm::vec3 _pos, float _width, float _height, float _length){
		Load(_pos.x, _pos.y, _pos.z, _width, _height, _length);
	}
};