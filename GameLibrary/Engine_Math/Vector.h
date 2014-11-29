#pragma once

#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>
#include <iostream>
#include <sstream>

#include "MathDefines.h"

namespace GameEngineLib{

	struct Vector3
	{
		/*Fields*/
		float x, y, z;
		//Loads x, y, and z into the Vector
		inline virtual void Load(float _x, float _y, float _z){
			x = _x; y = _y; z = _z;
		}
		//Default constructor
		inline Vector3(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f){
			Load(_x, _y, _z);
		}
		/*Operator Overloading*/
		//Assigning a vector to the vector
		inline Vector3& operator = (const Vector3& _v){
			x = _v.x; y = _v.y; z = _v.z;
			return *this;
		}
		//Negate the vector
		inline const Vector3 operator - () const{
			return Vector3(-x, -y, -z);
		}
		//Adding the vector by another vector and assigning it to itself
		inline Vector3& operator += (const Vector3& _v){
			x += _v.x; y += _v.y; z += _v.z;
			return *this;
		}
		//Adding the vector by another vector
		inline const Vector3 operator + (const Vector3& _v) const{
			Vector3 result = *this; //deep copy of this Vector3
			result += _v;			//using existing addition code
			return result;
		}
		//Subtracting the vector by another vector and assigning it to itself
		inline Vector3& operator -= (const Vector3& _v){
			*this += -_v;
			return *this;
		}
		//Subtracting the vector by another vector
		inline const Vector3 operator - (const Vector3& _v) const{
			Vector3 result = *this; //deep copy of this Vector3
			result -= _v;			//using existing subtraction code
			return result;
		}
		//Multiplying the vector by a scalar and assigning it to itself
		inline Vector3& operator *= (const float _s){
			x *= _s; y *= _s; z *= _s;
			return *this;
		}
		//Multiplying the vector by a scalar
		inline const Vector3 operator * (const float _s) const{
			Vector3 result = *this; //deep copy of this Vector3
			result *= _s;			//using existing multiplication method
			return result;
		}
		//Multiplying a scalar by the vector (in that order) by making the scalar a friend of the vector
		inline friend Vector3 operator * (const float _s, const Vector3& _v){
			return _v*_s;
		}
		//Dividing the vector by a scalar
		inline const Vector3 operator / (const float _s) const{
#ifdef _DEBUG
			if (fabs(_s) < VERY_SMALL){
				std::string errMsg = "ERROR: Dividing by nearly zero!";
				throw errMsg;
			}
#endif
			return Vector3(x / _s, y / _s, z / _s);
		}
		//Dividing the vector by a scalar and assigning it to itself
		inline Vector3& operator /= (const float _s){
#ifdef _DEBUG
			if (fabs(_s) < VERY_SMALL){
				std::string errMsg = "ERROR: Dividing by nearly zero!";
				throw errMsg;
			}
#endif
			*this *= (1.0f / _s);
			return *this;
		}
		//Comparison Operator
		inline bool operator == (const Vector3& _v){
			return (x == _v.x && y == _v.y && z == _v.z);
		}
		/*Other Functions*/
		//Converts to string
		inline const std::string toString() {
			std::stringstream ss;
			ss << std::string("(X:") << x << std::string(", Y:") << y << std::string(", Z:") << z << std::string(")");
			return ss.str();
		}
		//Prints the vector
		inline void print(){
			printf("(X: %f, Y: %f, Z: %f)\n", x, y, z);
		}
	};

	//Not a Quaternion
	struct Vector4 : public Vector3{
		float w;
		inline void Load(float _x, float _y, float _z, float _w){
			Vector3::Load(_x, _y, _z);
			w = _w;
		}
		inline Vector4(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f, float _w = 0.0f){
			Load(_x, _y, _z, _w);
		}
		/*Operator Overloading*/
		//Assigning a vector to the vector
		inline Vector4& operator = (const Vector4& _v){
			x = _v.x; y = _v.y; z = _v.z; w = _v.w;
			return *this;
		}
		//Negate the vector
		inline const Vector4 operator - () const{
			return Vector4(-x, -y, -z, -w);
		}
		/*Other Functions*/
		//Converts to string
		inline const std::string toString() {
			std::stringstream ss;
			ss << std::string("(X:") << x << std::string(", Y:") << y << std::string(", Z:") << z << std::string(", W:") << w << std::string(")");
			return ss.str();
		}
		//Prints the vector
		inline void print(){
			printf("(X: %f, Y: %f, Z: %f, W: %f)\n", x, y, z, w);
		}
	};

	struct Sphere : public Vector3{
		float r;
		inline void Load(float _x, float _y, float _z, float _r){
			x = _x; y = _y; z = _z; r = _r;
		}
	};

	struct Plane : public Vector3{

	};

};

#endif