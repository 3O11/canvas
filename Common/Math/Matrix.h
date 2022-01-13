#ifndef _CC_MATRIX_H
#define _CC_MATRIX_H

#include "Types.h"
#include "Vector.h"
#include "Point.h"

#include <array>

namespace cc
{
	struct Matrix3 final
	{
	public:
		Matrix3();
		Matrix3(Float val);
		Matrix3(const Vector3& row0, const Vector3& row1, const Vector3& row2);

		Vector3& operator[] (size_t index);
		const Vector3& operator[] (size_t index) const;

	private:
		std::array<Vector3, 3> m;
	};

	struct Matrix4 final
	{
	public:
		Matrix4();
		Matrix4(Float val);
		Matrix4(const Vector4& row0, const Vector4& row1, const Vector4& row2, const Vector4& row3);

		Vector4& operator[] (size_t index);
		const Vector4& operator[] (size_t index) const;

	private:
		std::array<Vector4, 4> m;
	};

	Matrix3 operator+ (const Matrix3& m, const Matrix3& n);
	Matrix3 operator- (const Matrix3& m, const Matrix3& n);
	Matrix3 operator* (const Matrix3& m, const Matrix3& n);

	Matrix3& operator+= (Matrix3& m, const Matrix3& n);
	Matrix3& operator-= (Matrix3& m, const Matrix3& n);
	Matrix3& operator*= (Matrix3& m, const Matrix3& n);

	Matrix4 operator+ (const Matrix4& m, const Matrix4& n);
	Matrix4 operator- (const Matrix4& m, const Matrix4& n);
	Matrix4 operator* (const Matrix4& m, const Matrix4& n);

	Matrix4& operator+= (Matrix4& m, const Matrix4& n);
	Matrix4& operator-= (Matrix4& m, const Matrix4& n);
	Matrix4& operator*= (Matrix4& m, const Matrix4& n);

	Vector2 operator* (const Matrix3& m, const Vector2& u);
	Vector3 operator* (const Matrix3& m, const Vector3& u);
	Vector3 operator* (const Matrix4& m, const Vector3& u);
	Vector4 operator* (const Matrix4& m, const Vector4& u);

	/* This has been cut out for now
	Vector4 operator* (const Vector4& u, const Matrix4& m);
	Vector3 operator* (const Vector3& u, const Matrix4& m);
	Vector3 operator* (const Vector3& u, const Matrix3& m);
	Vector2 operator* (const Vector2& u, const Matrix3& m);
	*/
}

#endif //_CC_MATRIX_H
