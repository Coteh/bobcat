#pragma once
#ifndef MATRIX4X4_H
#define MATRIX4X4_H
#include <stdio.h>	/// Needed for the printf statement, could have used cin and cout but I have issues.  
#include "Vector.h"

//Featuring commentary by the one and only Scott Fielder (as denoted by the triple /'s)

namespace  GameEngineLib {

	class Matrix4x4  {

		/// Let's just make sure that all is clear about how this matrix is layed out. 

		/// How a matrix is really layed out is pretty much abitrary but we need to agree
		/// and the world has agreed - except for microsoft - on the right-hand rule. 
		/// First, the 4x4 matrix is really just an array of 16 numbers.  
		/// We need to think of the array as a matrix in the following way
		/// 4x4 matrix - COLUMN MAJOR - The OpenGL, science, physics, mathematics and engeering way. 
		///	0	4	8	12			[0][0]	[1][0]	[2][0]	[3][0]   
		///	1	5	9	13	 (or)	[0][1]	[1][1]	[2][1]	[3][1]
		///	2	6	10	14			[0][2]	[1][2]	[2][2]	[3][2]
		///	3	7	11	15			[0][3]	[1][3]	[2][3]	[3][3]
	private:
		float  m[16];
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
		inline Matrix4x4(float xx, float xy, float xz, float xw,
			float yx, float yy, float yz, float yw,
			float zx, float zy, float zz, float zw,
			float wx, float wy, float wz, float ww) {
			m[0] = xx;   m[4] = xy;   m[8] = xz;   m[12] = xw;
			m[1] = yx;   m[5] = yy;   m[9] = yz;   m[13] = yw;
			m[2] = zx;   m[6] = zy;   m[10] = zz;   m[14] = zw;
			m[3] = wx;	  m[7] = wy;   m[11] = wz;	 m[15] = ww;
		}

		/// Create the unit matrix probably the most common way of initializing a matrix
		inline Matrix4x4(const float d = 1.0f) {
			if (d == 1.0f) {
				m[0] = 1.0f;   m[4] = 0.0f;   m[8] = 0.0f;   m[12] = 0.0f;
				m[1] = 0.0f;   m[5] = 1.0f;   m[9] = 0.0f;   m[13] = 0.0f;
				m[2] = 0.0f;   m[6] = 0.0f;   m[10] = 1.0f;   m[14] = 0.0f;
				m[3] = 0.0f;   m[7] = 0.0f;   m[11] = 0.0f;   m[15] = 1.0f;
			} else {
				/// Who knows maybe someone needs this - hope not...
				m[0] = d;   m[4] = d;   m[8] = d;   m[12] = d;
				m[1] = d;   m[5] = d;   m[9] = d;   m[13] = d;
				m[2] = d;   m[6] = d;   m[10] = d;   m[14] = d;
				m[3] = d;	 m[7] = d;   m[11] = d;	  m[15] = d;
			}
		}


		/// Creates the identity matrix
		inline void loadIdentity(){
			m[0] = 1.0f;   m[4] = 0.0f;   m[8] = 0.0f;   m[12] = 0.0f;
			m[1] = 0.0f;   m[5] = 1.0f;   m[9] = 0.0f;   m[13] = 0.0f;
			m[2] = 0.0f;   m[6] = 0.0f;   m[10] = 1.0f;   m[14] = 0.0f;
			m[3] = 0.0f;   m[7] = 0.0f;   m[11] = 0.0f;   m[15] = 1.0f;
		}



		/// Multiply two 4x4 matricies. 
		/// Grrr, I never liked mulipling maticies - but it needs to be done. 
		inline const Matrix4x4 operator*(const Matrix4x4& n) const {
			Matrix4x4 product;

			for (int i = 0; i < 4; i++){
				for (int j = 0; j < 4; j++){
					product[(i * 4) + j] = 0;
					for (int k = 0; k < 4; k++){
						product[(i * 4) + j] += m[(k * 4) + j] * n[(i * 4) + k];
					}
				}
			}

			return product;
		}

		/// Multipling a matrix by itself is probably the most commom
		/// (this is the address of the matrix. *this de-references that address - cool 
		inline Matrix4x4& operator*=(const Matrix4x4& n) {
			*this = *this * n;
			return *this;
		}

		/// Multiply a Vec4 by this matrix and return the resulting vector
		inline Vector4 operator* (const Vector4& v) const {
			return Vector4(v.x * m[0] + v.y * m[4] + v.z * m[8] + v.w * m[12],
				v.x * m[1] + v.y * m[5] + v.z * m[9] + v.w * m[13],
				v.x * m[2] + v.y * m[6] + v.z * m[10] + v.w * m[14],
				v.x * m[3] + v.y * m[7] + v.z * m[11] + v.w * m[15]);
		}


		inline void print() const {
			printf("%1.2f %1.2f %1.2f %1.2f\n%1.2f %1.2f %1.2f %1.2f\n%1.2f %1.2f %1.2f %1.2f\n%1.2f %1.2f %1.2f %1.2f\n\n",
				m[0], m[4], m[8], m[12],
				m[1], m[5], m[9], m[13],
				m[2], m[6], m[10], m[14],
				m[3], m[7], m[11], m[15]);
		}

		/// These allow me convert from type Matrix to const float * without issues
		inline operator float* () { return static_cast<float*>(&m[0]); }
		inline operator const float* () const { return static_cast<const float*>(&m[0]); }

	};
}
#endif