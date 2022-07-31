#ifndef _CC_VECTOR_H
#define _CC_VECTOR_H

namespace cc
{
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
