#ifndef _CC_VECTOR_H
#define _CC_VECTOR_H

#include "Types.h"

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
}

#endif //_CC_VECTOR_H
