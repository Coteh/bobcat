#include "VMath.h"
#include "MMath.h"
using namespace GameEngineLib;


///Tested Feb 2 2013 SSF
Matrix4x4 MMath::rotate(float angle, float x, float y, float z){
	float cosang, sinang, cosm;
	Matrix4x4 m;
	Vector3 rotAxis(x, y, z);
	rotAxis = VMath::normalize(rotAxis);

	angle *= DEGREES_TO_RADIANS;

	cosang = cos(angle);
	sinang = sin(angle);
	cosm = (1.0f - cosang);

	m[0] = (rotAxis.x * rotAxis.x * cosm) + cosang;
	m[1] = (rotAxis.x * rotAxis.y * cosm) + (rotAxis.z * sinang);
	m[2] = (rotAxis.x * rotAxis.z * cosm) - (rotAxis.y * sinang);
	m[3] = 0.0;
	m[4] = (rotAxis.x * rotAxis.y * cosm) - (rotAxis.z * sinang);
	m[5] = (rotAxis.y * rotAxis.y * cosm) + cosang;
	m[6] = (rotAxis.y * rotAxis.z * cosm) + (rotAxis.x * sinang);
	m[7] = 0.0;
	m[8] = (rotAxis.x * rotAxis.z * cosm) + (rotAxis.y * sinang);
	m[9] = (rotAxis.y * rotAxis.z * cosm) - (rotAxis.x * sinang);
	m[10] = (rotAxis.z * rotAxis.z * cosm) + cosang;
	m[11] = 0.0;
	m[12] = 0.0;
	m[13] = 0.0;
	m[14] = 0.0;
	m[15] = 1.0;
	return m;
}

Matrix4x4 MMath::rotate(float _angle, Vector3& _rotEuler){
	return rotate(_angle, _rotEuler.x, _rotEuler.y, _rotEuler.z);
}

Matrix4x4 MMath::rotate(Matrix4x4 _m, float _angle, Vector3& _rotEuler){
	return _m * rotate(_angle, _rotEuler);
}

///Tested Feb 1 2013 SSF
Matrix4x4 MMath::perspective(float fFov, float fAspect, float zMin, float zMax){
	Matrix4x4 m;
	m.loadIdentity();
	float yMax = zMin * tanf(fFov * 0.5f * DEGREES_TO_RADIANS);
	float yMin = -yMax;
	float xMin = yMin * fAspect;
	float xMax = -xMin;

	m[0] = (2.0f * zMin) / (xMax - xMin);
	m[5] = (2.0f * zMin) / (yMax - yMin);
	m[8] = (xMax + xMin) / (xMax - xMin);
	m[9] = (yMax + yMin) / (yMax - yMin);
	m[10] = -((zMax + zMin) / (zMax - zMin));
	m[11] = -1.0f;
	m[14] = -((2.0f * (zMax*zMin)) / (zMax - zMin));
	m[15] = 0.0f;
	return m;
}

/// Not tested but I'll bet I'm right
Matrix4x4 MMath::orthographic(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax){
	Matrix4x4 m;
	m[0] = 2.0f / (xMax - xMin);
	m[5] = 2.0f / (yMax - yMin);
	m[10] = -2.0f / (zMax - zMin);
	m[12] = -((xMax + xMin) / (xMax - xMin));
	m[13] = -((yMax + yMin) / (yMax - yMin));
	m[14] = -((zMax + zMin) / (zMax - zMin));
	m[15] = 1.0f;
	return m;
}

/// At first glance, it might look like this matrix 
/// is written left-handed or transposed, it has not. 
/// Remember how memory is layed out. It is still column based.  
///Tested Feb 1 2013 SSF  
Matrix4x4 MMath::translate(float x, float y, float z){
	return Matrix4x4(1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		x, y, z, 1.0f);
}

Matrix4x4 MMath::translate(Vector3& _v3){
	return translate(_v3.x, _v3.y, _v3.z);
}

Matrix4x4 MMath::translate(Matrix4x4& _m, Vector3& _v3){
	return _m * translate(_v3.x, _v3.y, _v3.z);
}

Matrix4x4 MMath::scale(float x, float y, float z){
	return Matrix4x4(x, 0.0f, 0.0f, 0.0f,
		0.0f, y, 0.0f, 0.0f,
		0.0f, 0.0f, z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4x4 MMath::scale(Vector3& _v3){
	return scale(_v3.x, _v3.y, _v3.z);
}

Matrix4x4 MMath::scale(Matrix4x4 _m, Vector3& _v3){
	return _m * scale(_v3);
}

Matrix4x4 MMath::transpose(const Matrix4x4& _m){
	Matrix4x4 returnMat;
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			returnMat[(4 * i) + j] = _m[(4 * j) + i];
		}
	}
	return returnMat;
}

/*
* Scott's version of inverse Matrix4
*/
Matrix4x4 MMath::inverse(const Matrix4x4& _m){
	Matrix4x4 inverseM;
	float det;

	inverseM[0] = _m[5] * _m[10] * _m[15] - _m[5] * _m[11] * _m[14] - _m[9] * _m[6] * _m[15] + _m[9] * _m[7] * _m[14] + _m[13] * _m[6] * _m[11] - _m[13] * _m[7] * _m[10];
	inverseM[1] = -_m[1] * _m[10] * _m[15] + _m[1] * _m[11] * _m[14] + _m[9] * _m[2] * _m[15] - _m[9] * _m[3] * _m[14] - _m[13] * _m[2] * _m[11] + _m[13] * _m[3] * _m[10];
	inverseM[2] = _m[1] * _m[6] * _m[15] - _m[1] * _m[7] * _m[14] - _m[5] * _m[2] * _m[15] + _m[5] * _m[3] * _m[14] + _m[13] * _m[2] * _m[7] - _m[13] * _m[3] * _m[6];
	inverseM[3] = -_m[1] * _m[6] * _m[11] + _m[1] * _m[7] * _m[10] + _m[5] * _m[2] * _m[11] - _m[5] * _m[3] * _m[10] - _m[9] * _m[2] * _m[7] + _m[9] * _m[3] * _m[6];
	inverseM[4] = -_m[4] * _m[10] * _m[15] + _m[4] * _m[11] * _m[14] + _m[8] * _m[6] * _m[15] - _m[8] * _m[7] * _m[14] - _m[12] * _m[6] * _m[11] + _m[12] * _m[7] * _m[10];
	inverseM[5] = _m[0] * _m[10] * _m[15] - _m[0] * _m[11] * _m[14] - _m[8] * _m[2] * _m[15] + _m[8] * _m[3] * _m[14] + _m[12] * _m[2] * _m[11] - _m[12] * _m[3] * _m[10];
	inverseM[6] = -_m[0] * _m[6] * _m[15] + _m[0] * _m[7] * _m[14] + _m[4] * _m[2] * _m[15] - _m[4] * _m[3] * _m[14] - _m[12] * _m[2] * _m[7] + _m[12] * _m[3] * _m[6];
	inverseM[7] = _m[0] * _m[6] * _m[11] - _m[0] * _m[7] * _m[10] - _m[4] * _m[2] * _m[11] + _m[4] * _m[3] * _m[10] + _m[8] * _m[2] * _m[7] - _m[8] * _m[3] * _m[6];
	inverseM[8] = _m[4] * _m[9] * _m[15] - _m[4] * _m[11] * _m[13] - _m[8] * _m[5] * _m[15] + _m[8] * _m[7] * _m[13] + _m[12] * _m[5] * _m[11] - _m[12] * _m[7] * _m[9];
	inverseM[9] = -_m[0] * _m[9] * _m[15] + _m[0] * _m[11] * _m[13] + _m[8] * _m[1] * _m[15] - _m[8] * _m[3] * _m[13] - _m[12] * _m[1] * _m[11] + _m[12] * _m[3] * _m[9];
	inverseM[10] = _m[0] * _m[5] * _m[15] - _m[0] * _m[7] * _m[13] - _m[4] * _m[1] * _m[15] + _m[4] * _m[3] * _m[13] + _m[12] * _m[1] * _m[7] - _m[12] * _m[3] * _m[5];
	inverseM[11] = -_m[0] * _m[5] * _m[11] + _m[0] * _m[7] * _m[9] + _m[4] * _m[1] * _m[11] - _m[4] * _m[3] * _m[9] - _m[8] * _m[1] * _m[7] + _m[8] * _m[3] * _m[5];
	inverseM[12] = -_m[4] * _m[9] * _m[14] + _m[4] * _m[10] * _m[13] + _m[8] * _m[5] * _m[14] - _m[8] * _m[6] * _m[13] - _m[12] * _m[5] * _m[10] + _m[12] * _m[6] * _m[9];
	inverseM[13] = _m[0] * _m[9] * _m[14] - _m[0] * _m[10] * _m[13] - _m[8] * _m[1] * _m[14] + _m[8] * _m[2] * _m[13] + _m[12] * _m[1] * _m[10] - _m[12] * _m[2] * _m[9];
	inverseM[14] = -_m[0] * _m[5] * _m[14] + _m[0] * _m[6] * _m[13] + _m[4] * _m[1] * _m[14] - _m[4] * _m[2] * _m[13] - _m[12] * _m[1] * _m[6] + _m[12] * _m[2] * _m[5];
	inverseM[15] = _m[0] * _m[5] * _m[10] - _m[0] * _m[6] * _m[9] - _m[4] * _m[1] * _m[10] + _m[4] * _m[2] * _m[9] + _m[8] * _m[1] * _m[6] - _m[8] * _m[2] * _m[5];

	det = _m[0] * inverseM[0] + _m[1] * inverseM[4] + _m[2] * inverseM[8] + _m[3] * inverseM[12];

#ifdef _DEBUG  /// If in debug mode let's worry about divide by zero or nearly zero!!! 
	if (fabs(det) < VERY_SMALL) {
		std::string errorMsg("Divide by nearly zero! ");
		throw errorMsg;
	}
#endif
	det = 1.0f / det;
	for (int i = 0; i < 16; i++){
		inverseM[i] *= det;
	}
	return inverseM;
}

Matrix3x3 MMath::transpose(const Matrix3x3& _m3){
	Matrix3x3 returnMat;
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			returnMat[(3 * i) + j] = _m3[(3 * j) + i];
		}
	}
	return returnMat;
}

const float MMath::determinant(const Matrix3x3& _m3){
	return (_m3[2] * _m3[3] * _m3[7]) + (_m3[1] * _m3[5] * _m3[6]) + (_m3[0] * _m3[4] * _m3[8]) - (_m3[8] * _m3[3] * _m3[1]) - (_m3[7] * _m3[5] * _m3[0]) - (_m3[6] * _m3[4] * _m3[2]);
}

//Getting the adjugate via the conjugate/matrix of minors method
Matrix3x3 MMath::adjugate(const Matrix3x3& _m3){
	Matrix3x3 adjugate = Matrix3x3(((_m3[4] * _m3[8]) - (_m3[7] * _m3[5])), -((_m3[1] * _m3[8]) - (_m3[7] * _m3[2])), ((_m3[1] * _m3[5]) - (_m3[4] * _m3[2])),
		-((_m3[3] * _m3[8]) - (_m3[6] * _m3[5])), ((_m3[0] * _m3[8]) - (_m3[6] * _m3[2])), -((_m3[0] * _m3[5]) - (_m3[3] * _m3[2])),
		((_m3[3] * _m3[7]) - (_m3[6] * _m3[4])), -((_m3[0] * _m3[7]) - (_m3[6] * _m3[1])), ((_m3[0] * _m3[4]) - (_m3[3] * _m3[1])));
	return transpose(adjugate);
}

//The inverse of a matrix is equal to the adjugate of the matrix
//divided by the determinant of the matrix
Matrix3x3 MMath::inverse(const Matrix3x3& _m3){
	Matrix3x3 returnMat;
	float det = determinant(_m3);
	returnMat = adjugate(_m3) * (1 / det);
	return returnMat;
}

///Tested Feb 1 2013 SSF
Matrix4x4 MMath::lookAt(float eyeX, float eyeY, float eyeZ,
	float atX, float atY, float atZ,
	float upX, float upY, float upZ){

	/// These are the default vectors of the eye according to OpenGL
	///	origin(0.0f,0.0f,0.0f);
	/// up(0.0f,1.0f,0.0f);
	/// forward(0.0f,0.0f,-1.0f);

	Vector3 at(atX, atY, atZ);
	Vector3 up(upX, upY, upZ);
	Vector3 eye(eyeX, eyeY, eyeZ);

	Matrix4x4 result;

	Vector3 forward = VMath::normalize(at - eye);
	up = VMath::normalize(up);
	Vector3 side = VMath::normalize(VMath::cross(forward, up));
	up = VMath::cross(side, forward);

	result[0] = side.x;
	result[1] = side.y;
	result[2] = side.z;
	result[3] = 0.0;

	result[4] = up.x;
	result[5] = up.y;
	result[6] = up.z;
	result[7] = 0.0;

	result[8] = -forward.x;
	result[9] = -forward.y;
	result[10] = -forward.z;
	result[11] = 0.0;

	result[12] = -VMath::dot(side, eye);
	result[13] = -VMath::dot(up, eye);
	result[14] = VMath::dot(forward, eye);
	result[15] = 1.0;

	return result;
}