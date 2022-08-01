#ifndef _CC_MATRIX_H
#define _CC_MATRIX_H

#include <array>

#include "Vector.h"

namespace cc
{
	template <typename T>
	struct Matrix3T final
	{
	public:
		explicit Matrix3T();
		explicit Matrix3T(T val);
		explicit Matrix3T(const Vector3T<T>& row0, const Vector3T<T>& row1, const Vector3T<T>& row2);

		Vector3T<T>& operator[] (size_t index);
		const Vector3T<T>& operator[] (size_t index) const;

		Matrix3T<T>& Transpose();
		Matrix3T<T> Transposed() const;

		// TODO: These are not implemented yet
		Matrix3T<T>& Invert();
		Matrix3T<T> Inverse() const;
		T Det() const;

	private:
		std::array<Vector3T<T>, 3> m;
	};

	template <typename T>
	struct Matrix4T final
	{
	public:
		explicit Matrix4T();
		explicit Matrix4T(T val);
		explicit Matrix4T(const Vector4T<T>& row0, const Vector4T<T>& row1, const Vector4T<T>& row2, const Vector4T<T>& row3);

		Vector4T<T>& operator[] (size_t index);
		const Vector4T<T>& operator[] (size_t index) const;

		Matrix4T<T>& Transpose();
		Matrix4T<T> Transposed() const;

		// TODO: These are not implemented yet
		Matrix4T<T>& Invert();
		Matrix4T<T> Inverse() const;
		T Det() const;

	private:
		std::array<Vector4T<T>, 4> m;
	};

	template <typename T>
	Matrix3T<T> operator+ (const Matrix3T<T>& m, const Matrix3T<T>& n);
	template <typename T>
	Matrix3T<T> operator- (const Matrix3T<T>& m, const Matrix3T<T>& n);
	template <typename T>
	Matrix3T<T> operator* (const Matrix3T<T>& m, const Matrix3T<T>& n);

	template <typename T>
	Matrix3T<T>& operator+= (Matrix3T<T>& m, const Matrix3T<T>& n);
	template <typename T>
	Matrix3T<T>& operator-= (Matrix3T<T>& m, const Matrix3T<T>& n);
	template <typename T>
	Matrix3T<T>& operator*= (Matrix3T<T>& m, const Matrix3T<T>& n);

	template <typename T>
	Matrix4T<T> operator+ (const Matrix4T<T>& m, const Matrix4T<T>& n);
	template <typename T>
	Matrix4T<T> operator- (const Matrix4T<T>& m, const Matrix4T<T>& n);
	template <typename T>
	Matrix4T<T> operator* (const Matrix4T<T>& m, const Matrix4T<T>& n);

	template <typename T>
	Matrix4T<T>& operator+= (Matrix4T<T>& m, const Matrix4T<T>& n);
	template <typename T>
	Matrix4T<T>& operator-= (Matrix4T<T>& m, const Matrix4T<T>& n);
	template <typename T>
	Matrix4T<T>& operator*= (Matrix4T<T>& m, const Matrix4T<T>& n);

	template <typename T>
	Vector2T<T> operator* (const Matrix3T<T>& m, const Vector2T<T>& u);
	template <typename T>
	Vector3T<T> operator* (const Matrix3T<T>& m, const Vector3T<T>& u);
	template <typename T>
	Vector3T<T> operator* (const Matrix4T<T>& m, const Vector3T<T>& u);
	template <typename T>
	Vector4T<T> operator* (const Matrix4T<T>& m, const Vector4T<T>& u);

	template <typename T>
	Vector4T<T> operator* (const Vector4T<T>& u, const Matrix4T<T>& m);
	template <typename T>
	Vector3T<T> operator* (const Vector3T<T>& u, const Matrix4T<T>& m);
	template <typename T>
	Vector3T<T> operator* (const Vector3T<T>& u, const Matrix3T<T>& m);
	template <typename T>
	Vector2T<T> operator* (const Vector2T<T>& u, const Matrix3T<T>& m);
}

#include "Matrix.inl"

#endif //_CC_MATRIX_H
