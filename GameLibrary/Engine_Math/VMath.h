#pragma once

#ifndef VMATH_H
#define VMATH_H

#include <math.h>
#include "Vector.h"

namespace GameEngineLib{

	class VMath
	{
	public:
		VMath();

		//Gets the magnitude of the vector
		inline static const float mag(const Vector3& _v){
			return sqrt((_v.x * _v.x) + (_v.y * _v.y) + (_v.z * _v.z));
		}
		//Normalizes the Vector
		inline static const Vector3 normalize(const Vector3& _v){
			float magnitude = mag(_v);
			return Vector3(_v.x / magnitude, _v.y / magnitude, _v.z / magnitude);
		}
		//Dot products the vector
		inline static const float dot(const Vector3& _v, const Vector3& _v2){
			return ((_v.x * _v2.x) + (_v.y * _v2.y) + (_v.z * _v2.z));
		}
		//Cross products the vector
		inline static const Vector3 cross(const Vector3& _v, const Vector3& _v2){
			return Vector3((_v.y * _v2.z - _v.z * _v2.y), 
				(_v.z * _v2.x - _v.x * _v2.z), 
				(_v.x * _v2.y - _v.y * _v2.x));
		}

		/// Reflect a normalized direction Vec3 off a plane 
		static Vector3 reflect(const Vector3 v, const Plane p);

		/// Reflect a velocity Vec3 off a plane maintaining the original velocity 
		static Vector3 reflect2(const Vector3 v, const Plane p);

		/// Get the distance between two Vec3s 
		static float distance(const Vector3 &a, const Vector3 &b);

		/// Get the distance between a point (Vec3) and a plane 
		static float distance(const Vector3 &v, const Plane &p);

		/// Get the distance between a sphere and a plane
		static float distance(const Sphere &s, const Plane &p);
	};

};

#endif