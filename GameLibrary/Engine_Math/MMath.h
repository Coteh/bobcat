#pragma once

#ifndef MMATH_H
#define MMATH_H

#include <math.h>
#include "Matrix4x4.h"
#include "Matrix3x3.h"

namespace GameEngineLib{
	class MMath{
	public:
		static Matrix4x4 perspective(float _fFov, float _fAspect, float _zMin, float _zMax);
		static Matrix4x4 rotate(float _angle, float _x, float _y, float _z);
		static Matrix4x4 translate(float _x, float _y, float _z);
		static Matrix4x4 scale(float x, float y, float z);
		static Matrix4x4 transpose(const Matrix4x4& _m);
		static Matrix4x4 inverse(const Matrix4x4& _m);
		static Matrix3x3 transpose(const Matrix3x3& _m3);
		static const float determinant(const Matrix3x3& _m3);
		static Matrix3x3 adjugate(const Matrix3x3& _m3);
		static Matrix3x3 inverse(const Matrix3x3& _m3);
		static Matrix4x4 lookAt(float eyeX, float eyeY, float eyeZ,
			float atX, float atY, float atZ,
			float upX, float upY, float upZ);
		static Matrix4x4 orthographic(float _xMin, float _xMax, float _yMin, float _yMax, float _zMin, float _zMax);
	};
}

#endif