#pragma once
#ifndef MATRIX3X3_H
#define MATRIX3X3_H
#include <stdio.h>
#include "Matrix4x4.h"
#include "Vector.h"

namespace  GameEngineLib {

	class Matrix3x3  {
	private:
		float  m[9];
	public:

		/// Now I can use the structure itself as an array.
		/// When overloading the [] operator you need to declare one
		/// to read the array and one to write to the array. 
		///  Returns a const rvalue
		inline const float operator [] (int index) const {
			return *(m + index);
		}

		/// This one is for writing to the structure as if where an array 
		/// it returns a lvalue
		inline float& operator [] (int index) {
			return *(m + index);
		}


		/// Constuctors
		inline Matrix3x3(float xx, float xy, float xz,
			float yx, float yy, float yz,
			float zx, float zy, float zz) {
			m[0] = xx;   m[3] = xy;   m[6] = xz;
			m[1] = yx;   m[4] = yy;   m[7] = yz;
			m[2] = zx;   m[5] = zy;   m[8] = zz;
		}

		/// Create the unit matrix probably the most common way of initializing a matrix
		inline Matrix3x3(const float d = 1.0f) {
			if (d == 1.0f) {
				m[0] = 1.0f;   m[3] = 0.0f;   m[6] = 0.0f;
				m[1] = 0.0f;   m[4] = 1.0f;   m[7] = 0.0f;
				m[2] = 0.0f;   m[5] = 0.0f;   m[8] = 1.0f;
			} else {
				/// Who knows maybe someone needs this - hope not...
				m[0] = d;   m[3] = d;   m[6] = d;
				m[1] = d;   m[4] = d;   m[7] = d;
				m[2] = d;   m[5] = d;   m[8] = d;
			}
		}

		inline Matrix3x3(const Matrix4x4& _matrix){
			m[0] = _matrix[0]; m[3] = _matrix[4]; m[6] = _matrix[7];
			m[1] = _matrix[1]; m[4] = _matrix[5]; m[7] = _matrix[9];
			m[2] = _matrix[2]; m[5] = _matrix[6]; m[8] = _matrix[10];
		}

		/// Creates the identity matrix
		inline void loadIdentity(){
			m[0] = 1.0f;   m[3] = 0.0f;   m[6] = 0.0f;
			m[1] = 0.0f;   m[4] = 1.0f;   m[7] = 0.0f;
			m[2] = 0.0f;   m[5] = 0.0f;   m[8] = 1.0f;
		}



		/// Multiply two 3x3 matricies. 
		/// Grrr, I never liked mulipling maticies - but it needs to be done. 
		inline const Matrix3x3 operator*(const Matrix3x3& n) const {
			Matrix3x3 product;

			for (int i = 0; i < 3; i++){
				for (int j = 0; j < 3; j++){
					product[(i * 3) + j] = 0;
					for (int k = 0; k < 3; k++){
						product[(i * 3) + j] += m[(k * 3) + j] * n[(i * 3) + k];
					}
				}
			}

			return product;
		}

		/// Multipling a matrix by itself is probably the most commom
		/// (this is the address of the matrix. *this de-references that address - cool 
		inline Matrix3x3& operator*=(const Matrix3x3& n) {
			*this = *this * n;
			return *this;
		}

		/// Multiply a Vec3 by this matrix and return the resulting vector
		inline Vector3 operator* (const Vector3& v) const {
			return Vector3(v.x * m[0] + v.y * m[3] + v.z * m[6],
				v.x * m[1] + v.y * m[4] + v.z * m[7],
				v.x * m[2] + v.y * m[5] + v.z * m[8]);
		}

		//Multiply a Matrix by a float and return the resulting matrix
		inline const Matrix3x3& operator*(const float _f) const{
			Matrix3x3 product;

			for (int i = 0; i < 9; i++){
				product[i] = m[i] * _f;
			}

			return product;
		}


		inline void print() const {
			printf("%1.2f %1.2f %1.2f\n%1.2f %1.2f %1.2f\n%1.2f %1.2f %1.2f\n\n",
				m[0], m[3], m[6],
				m[1], m[4], m[7],
				m[2], m[5], m[8]);
		}

		/// These allow me convert from type Matrix to const float * without issues
		inline operator float* () { return static_cast<float*>(&m[0]); }
		inline operator const float* () const { return static_cast<const float*>(&m[0]); }

	};
}
#endif