#ifndef _CC_MATRIX_H
#define _CC_MATRIX_H

#include "Types.h"
#include "Vector.h"
#include "Point.h"

#include <array>

// TODO: add templates for additional matrix types, same as in Vector.h

namespace cc
{
	struct Matrix3 final
	{
	public:
		explicit Matrix3();
		explicit Matrix3(Float val);
		explicit Matrix3(const Vector3& row0, const Vector3& row1, const Vector3& row2);

		Vector3& operator[] (size_t index);
		const Vector3& operator[] (size_t index) const;

		Matrix3& Transpose();
		Matrix3 Transposed() const;

		// TODO: These are not implemented yet
		Matrix3& Invert();
		Matrix3 Inverse() const;
		Float Det() const;

	private:
		std::array<Vector3, 3> m;
	};

	struct Matrix4 final
	{
	public:
		explicit Matrix4();
		explicit Matrix4(Float val);
		explicit Matrix4(const Vector4& row0, const Vector4& row1, const Vector4& row2, const Vector4& row3);

		Vector4& operator[] (size_t index);
		const Vector4& operator[] (size_t index) const;

		Matrix4& Transpose();
		Matrix4 Transposed() const;

		// TODO: These are not implemented yet
		Matrix4& Invert();
		Matrix4 Inverse() const;
		Float Det() const;

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

	Vector4 operator* (const Vector4& u, const Matrix4& m);
	Vector3 operator* (const Vector3& u, const Matrix4& m);
	Vector3 operator* (const Vector3& u, const Matrix3& m);
	Vector2 operator* (const Vector2& u, const Matrix3& m);


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
