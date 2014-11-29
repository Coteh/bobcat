#pragma once

#ifndef QUATERNION_H
#define QUATERNION_H
#include "Vector.h"
#include "VMath.h"

namespace GameEngineLib{

	struct Quaternion : Vector3{
		float w;

		//Load the values in
		inline void Load(float _w, float _x, float _y, float _z) {
			w = _w; x = _x; y = _y; z = _z;
		}

		inline Quaternion(){
			Load(1.0f, 0.0f, 0.0f, 0.0f);
		}

		//Rotation Constructor
		inline Quaternion(float _angle, const Vector3& _v){
			_angle *= DEGREES_TO_RADIANS;
			Load(cos(_angle / 2.0f), sin(_angle / 2.0f) * _v.x, sin(_angle / 2.0f) * _v.y, sin(_angle / 2.0f) * _v.z);
		}

		inline Quaternion(float _w, float _x, float _y, float _z){
			Load(_w, _x, _y, _z);
		}

		//Copy Constructor
		inline Quaternion(const Quaternion& _q) {
			Load(_q.w, _q.x, _q.y, _q.z);
		}

		//Assignment Operator
		inline Quaternion& operator = (const Quaternion& _q){
			Load(_q.w, _q.x, _q.y, _q.z);
			return *this;
		}

		//Return the negative of a quaternion
		inline Quaternion& operator - (){
			return Quaternion(-w, -x, -y, -z);
		}

		//Multiplying the quaternion by another quaternion
		inline const Quaternion operator * (const Quaternion& _q) const{
			return Quaternion(w * _q.w - VMath::dot(*this, _q), VMath::cross(*this, _q));
		}

		/// Multiply a quaternion by a Vec3 - using the right-hand rule 
		inline const Quaternion operator * (const Vector4& v) const {
			Vector3 ijk(w*v + v.w * (*this) + VMath::cross(*this, v));
			return Quaternion(w * v.w - VMath::dot(*this, v), ijk.x, ijk.y, ijk.z);
		}


		inline const Quaternion conjugate() const {
			return Quaternion(w, -x, -y, -z);
		}

		inline Vector3 rotate(const Vector3& v){
			/// This is the standard way q*v*q^-1
			///return Vec3( (*this) * v * (*this).conjugate());

			/// I read a paper that shows this way to be faster and it works! 
			Vector3 v2 = VMath::cross(*this, v);
			return v + v2 * (2.0f * w) + VMath::cross(*this, v2) * 2.0f;
		}


		inline  Matrix4x4 toMatrix(){
			/// This is the fastest way I know...
			return Matrix4x4((1.0f - 2.0f*y*y - 2.0f*z*z), (2.0f*x*y + 2.0f * z*w), (2.0f*x*z - 2.0f*y*w), 0.0f,
				(2.0f*x*y - 2.0f*z*w), (1.0f - 2.0f*x*x - 2.0f*z*z), (2 * y*z + 2 * x*w), 0.0f,
				(2.0f*x*z + 2.0f*y*w), (2.0f*y*z - 2 * x*w), (1.0f - 2.0f*x*x - 2.0f*y*y), 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f);

			/// ... but this is the coolest . My way is just a bit faster on single processor machines
			/// but this method is faster on parallel multicore machines.
			/*Matrix m1(  w,   z,  -y,  x,
			-z,   w,   x,  y,
			y,  -x,   w,  z,
			-x,  -y,  -z,  w);

			Matrix m2(  w,   z, -y, -x,
			-z,   w,  x, -y,
			y,  -x,  w, -z,
			-x,   y,  z,  w);
			return m1 * m2;*/
		}


		/// To work this out you can multipy the three angles as quaternions together. 
		/// q = q(yaw) * q(pitch) * q(yaw) the result is as follows
		inline const Quaternion fromEuler(float _yaw, float _pitch, float _roll){
			float cosYaw = cos(0.5f *_yaw * DEGREES_TO_RADIANS);
			float cosPitch = cos(0.5f * _pitch * DEGREES_TO_RADIANS);
			float cosRoll = cos(0.5f  *_roll * DEGREES_TO_RADIANS);
			float sinYaw = sin(0.5f *_yaw * DEGREES_TO_RADIANS);
			float sinPitch = sin(0.5f * _pitch * DEGREES_TO_RADIANS);
			float sinRoll = sin(0.5f  *_roll * DEGREES_TO_RADIANS);
			return Quaternion(
				(cosYaw * cosPitch * cosRoll) + (sinYaw * sinPitch * sinRoll),
				(cosYaw * cosPitch * sinRoll) - (sinYaw * sinPitch * cosRoll),
				(cosYaw * sinPitch * cosRoll) + (sinYaw * cosPitch * sinRoll),
				(sinYaw * cosPitch * cosRoll) - (cosYaw * sinPitch * sinRoll));
		}


		inline void print() {
			printf("%f %f %f %f\n", w, x, y, z);
		}
	};

};

#endif