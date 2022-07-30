#ifndef _CC_VECTOR_H
#define _CC_VECTOR_H

#include "Types.h"

// TODO: Add templates for additional Vector types, e.g. Vector3d, Vector3i

namespace cc
{
	struct Vector2 final
	{
		Vector2();
		Vector2(Float val);
		Vector2(Float x, Float y);

		Float& operator[] (size_t index);
		const Float& operator[] (size_t index) const;

		static Float Dot(const Vector2& u, const Vector2& v);
		Float LengthSquared();
		Float Length();

		Vector2& Normalize();
		Vector2 Normalized() const;

		Float x;
		Float y;
	};

	struct Vector3 final
	{
		Vector3();
		Vector3(Float val);
		Vector3(Float x, Float y, Float z);
		Vector3(const Vector2& vec);

		Float& operator[] (size_t index);
		const Float& operator[] (size_t index) const;

		static Float Dot(const Vector3& u, const Vector3& v);
		Float LengthSquared();
		Float Length();

		Vector3& Normalize();
		Vector3 Normalized() const;

		static Vector3 Cross(const Vector3& u, const Vector3& v);

		Float x;
		Float y;
		Float z;
	};

	struct Vector4 final
	{
		Vector4();
		Vector4(Float val);
		Vector4(Float x, Float y, Float z);
		Vector4(Float x, Float y, Float z, Float w);
		Vector4(const Vector3& vec);
		Vector4(const Vector3& vec, Float w);

		Float& operator[] (size_t index);
		const Float& operator[] (size_t index) const;

		static Float Dot(const Vector4& u, const Vector4& v);
		Float LengthSquared();
		Float Length();

		Vector4& Normalize();
		Vector4 Normalized() const;

		Float x;
		Float y;
		Float z;
		Float w;
	};

	Vector2 operator+ (const Vector2& u, const Vector2& v);
	Vector2 operator- (const Vector2& u, const Vector2& v);
	Vector2 operator* (const Vector2& u, const Vector2& v);
	Vector2 operator/ (const Vector2& u, const Vector2& v);
	Vector2 operator- (const Vector2& u);

	Vector2& operator+= (Vector2& u, const Vector2& v);
	Vector2& operator-= (Vector2& u, const Vector2& v);
	Vector2& operator*= (Vector2& u, const Vector2& v);
	Vector2& operator/= (Vector2& u, const Vector2& v);

	Vector3 operator+ (const Vector3& u, const Vector3& v);
	Vector3 operator- (const Vector3& u, const Vector3& v);
	Vector3 operator* (const Vector3& u, const Vector3& v);
	Vector3 operator/ (const Vector3& u, const Vector3& v);
	Vector3 operator- (const Vector3& u);

	Vector3& operator+= (Vector3& u, const Vector3& v);
	Vector3& operator-= (Vector3& u, const Vector3& v);
	Vector3& operator*= (Vector3& u, const Vector3& v);
	Vector3& operator/= (Vector3& u, const Vector3& v);

	Vector4 operator+ (const Vector4& u, const Vector4& v);
	Vector4 operator- (const Vector4& u, const Vector4& v);
	Vector4 operator* (const Vector4& u, const Vector4& v);
	Vector4 operator/ (const Vector4& u, const Vector4& v);
	Vector4 operator- (const Vector4& u);

	Vector4& operator+= (Vector4& u, const Vector4& v);
	Vector4& operator-= (Vector4& u, const Vector4& v);
	Vector4& operator*= (Vector4& u, const Vector4& v);
	Vector4& operator/= (Vector4& u, const Vector4& v);

	template <typename T>
	struct Vector2T final
	{
		Vector2T();
		Vector2T(T val);
		Vector2T(T x, T y);

		T& operator[] (size_t index);
		const T& operator[] (size_t index) const;

		static T Dot(const Vector2T<T>& u, const Vector2T<T>& v);
		T LengthSquared();
		T Length();

		Vector2T<T>& Normalize();
		Vector2T<T> Normalized() const;

		T x;
		T y;
	};

	template <typename T>
	struct Vector3T final
	{
		Vector3T();
		Vector3T(T val);
		Vector3T(T x, T y, T z);
		Vector3T(const Vector2T<T>& vec);

		T& operator[] (size_t index);
		const T& operator[] (size_t index) const;

		static T Dot(const Vector3T<T>& u, const Vector3T<T>& v);
		T LengthSquared();
		T Length();

		Vector3T<T>& Normalize();
		Vector3T<T> Normalized() const;

		static Vector3T<T> Cross(const Vector3T<T>& u, const Vector3T<T>& v);

		T x;
		T y;
		T z;
	};

	template <typename T>
	struct Vector4T final
	{
		Vector4T();
		Vector4T(T val);
		Vector4T(T x, T y, T z);
		Vector4T(T x, T y, T z, T w);
		Vector4T(const Vector3T<T>& vec);
		Vector4T(const Vector3T<T>& vec, T w);

		T& operator[] (size_t index);
		const T& operator[] (size_t index) const;

		static T Dot(const Vector4T<T>& u, const Vector4T<T>& v);
		T LengthSquared();
		T Length();

		Vector4T<T>& Normalize();
		Vector4T<T> Normalized() const;

		T x;
		T y;
		T z;
		T w;
	};

	template <typename T>
	Vector2T<T> operator+ (const Vector2T<T>& u, const Vector2T<T>& v);
	template <typename T>
	Vector2T<T> operator- (const Vector2T<T>& u, const Vector2T<T>& v);
	template <typename T>
	Vector2T<T> operator* (const Vector2T<T>& u, const Vector2T<T>& v);
	template <typename T>
	Vector2T<T> operator/ (const Vector2T<T>& u, const Vector2T<T>& v);
	template <typename T>
	Vector2T<T> operator- (const Vector2T<T>& u);

	template <typename T>
	Vector2T<T>& operator+= (Vector2T<T>& u, const Vector2T<T>& v);
	template <typename T>
	Vector2T<T>& operator-= (Vector2T<T>& u, const Vector2T<T>& v);
	template <typename T>
	Vector2T<T>& operator*= (Vector2T<T>& u, const Vector2T<T>& v);
	template <typename T>
	Vector2T<T>& operator/= (Vector2T<T>& u, const Vector2T<T>& v);

	template <typename T>
	Vector3T<T> operator+ (const Vector3T<T>& u, const Vector3T<T>& v);
	template <typename T>
	Vector3T<T> operator- (const Vector3T<T>& u, const Vector3T<T>& v);
	template <typename T>
	Vector3T<T> operator* (const Vector3T<T>& u, const Vector3T<T>& v);
	template <typename T>
	Vector3T<T> operator/ (const Vector3T<T>& u, const Vector3T<T>& v);
	template <typename T>
	Vector3T<T> operator- (const Vector3T<T>& u);

	template <typename T>
	Vector3T<T>& operator+= (Vector3T<T>& u, const Vector3T<T>& v);
	template <typename T>
	Vector3T<T>& operator-= (Vector3T<T>& u, const Vector3T<T>& v);
	template <typename T>
	Vector3T<T>& operator*= (Vector3T<T>& u, const Vector3T<T>& v);
	template <typename T>
	Vector3T<T>& operator/= (Vector3T<T>& u, const Vector3T<T>& v);

	template <typename T>
	Vector4T<T> operator+ (const Vector4T<T>& u, const Vector4T<T>& v);
	template <typename T>
	Vector4T<T> operator- (const Vector4T<T>& u, const Vector4T<T>& v);
	template <typename T>
	Vector4T<T> operator* (const Vector4T<T>& u, const Vector4T<T>& v);
	template <typename T>
	Vector4T<T> operator/ (const Vector4T<T>& u, const Vector4T<T>& v);
	template <typename T>
	Vector4T<T> operator- (const Vector4T<T>& u);

	template <typename T>
	Vector4T<T>& operator+= (Vector4T<T>& u, const Vector4T<T>& v);
	template <typename T>
	Vector4T<T>& operator-= (Vector4T<T>& u, const Vector4T<T>& v);
	template <typename T>
	Vector4T<T>& operator*= (Vector4T<T>& u, const Vector4T<T>& v);
	template <typename T>
	Vector4T<T>& operator/= (Vector4T<T>& u, const Vector4T<T>& v);
}

#include "Vector.inl"

#endif //_CC_VECTOR_H
