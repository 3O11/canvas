#include "Vector.h"

#include <cmath>

namespace cc
{
	Vector2::Vector2()
		: x(0.0), y(0.0)
	{}

	Vector2::Vector2(Float val)
		: x(val), y(val)
	{}

	Vector2::Vector2(Float x, Float y)
		: x(x), y(y)
	{}

	Float& Vector2::operator[](size_t index)
	{
		if (index == 0) return x;
		return y;
	}

	const Float& Vector2::operator[](size_t index) const
	{
		if (index == 0) return x;
		return y;
	}

	Float Vector2::Dot(const Vector2& u, const Vector2& v)
	{
		return u.x * v.x + u.y * v.y;
	}

	Float Vector2::LengthSquared()
	{
		return Dot(*this, *this);
	}

	Float Vector2::Length()
	{
		return std::sqrt(LengthSquared());
	}

	Vector2& Vector2::Normalize()
	{
		Float length = Length();
		x /= length;
		y /= length;

		return *this;
	}

	Vector2 Vector2::Normalized() const
	{
		return Vector2(*this).Normalize();
	}


	Vector3::Vector3()
		: x(0.0), y(0.0), z(0.0)
	{}

	Vector3::Vector3(Float val)
		: x(val), y(val), z(val)
	{}

	Vector3::Vector3(Float x, Float y, Float z)
		: x(x), y(y), z(z)
	{}

	Vector3::Vector3(const Vector2 & vec)
		: x(vec.x), y(vec.y), z(0.0)
	{}

	Float& Vector3::operator[](size_t index)
	{
		if (index == 0) return x;
		if (index == 1) return y;
		return z;
	}

	const Float& Vector3::operator[](size_t index) const
	{
		if (index == 0) return x;
		if (index == 1) return y;
		return z;
	}

	Float Vector3::Dot(const Vector3& u, const Vector3& v)
	{
		return u.x * v.x + u.y * v.y + u.z * v.z;
	}

	Float Vector3::LengthSquared()
	{
		return Dot(*this, *this);
	}

	Float Vector3::Length()
	{
		return std::sqrt(LengthSquared());
	}

	Vector3& Vector3::Normalize()
	{
		Float length = Length();
		x /= length;
		y /= length;
		z /= length;

		return *this;
	}

	Vector3 Vector3::Normalized() const
	{
		return Vector3(*this).Normalize();
	}

	Vector3 Vector3::Cross(const Vector3& u, const Vector3& v)
	{
		Vector3 c;

		c.x = u.y * v.z - u.z * v.y;
		c.y = u.z * v.x - u.x * v.z;
		c.z = u.x * v.y - u.y * v.x;

		return c;
	}


	Vector4::Vector4()
		: x(0.0), y(0.0), z(0.0), w(0.0)
	{}

	Vector4::Vector4(Float val)
		: x(val), y(val), z(val), w(val)
	{}

	Vector4::Vector4(Float x, Float y, Float z)
		: x(x), y(y), z(z), w(1.0)
	{}

	Vector4::Vector4(Float x, Float y, Float z, Float w)
		: x(x), y(y), z(z), w(w)
	{}

	Vector4::Vector4(const Vector3& vec)
		: x(vec.x), y(vec.y), z(vec.z), w(1.0)
	{}

	Vector4::Vector4(const Vector3& vec, Float w)
		: x(vec.x), y(vec.y), z(vec.z), w(w)
	{}

	Float& Vector4::operator[](size_t index)
	{
		if (index == 0) return x;
		if (index == 1) return y;
		if (index == 2) return z;
		return w;
	}

	const Float& Vector4::operator[](size_t index) const
	{
		if (index == 0) return x;
		if (index == 1) return y;
		if (index == 2) return z;
		return w;
	}

	Float Vector4::Dot(const Vector4& u, const Vector4& v)
	{
		return u.x * v.x + u.y * v.y + u.z * v.z + u.w * v.w;
	}

	Float Vector4::LengthSquared()
	{
		return Dot(*this, *this);
	}

	Float Vector4::Length()
	{
		return std::sqrt(LengthSquared());
	}

	Vector4& Vector4::Normalize()
	{
		Float length = Length();
		x /= length;
		y /= length;
		z /= length;
		w /= length;

		return *this;
	}

	Vector4 Vector4::Normalized() const
	{
		return Vector4(*this).Normalize();
	}


	Vector2 operator+(const Vector2& u, const Vector2& v)
	{
		return {u.x + v.x, u.y + v.y};
	}

	Vector2 operator-(const Vector2& u, const Vector2& v)
	{
		return { u.x - v.x, u.y - v.y };
	}

	Vector2 operator*(const Vector2& u, const Vector2& v)
	{
		return { u.x * v.x, u.y * v.y };
	}

	Vector2 operator/(const Vector2& u, const Vector2& v)
	{
		return { u.x / v.x, u.y / v.y };
	}

	Vector2 operator-(const Vector2& u)
	{
		return { -u.x, -u.y };
	}


	Vector2& operator+=(Vector2& u, const Vector2& v)
	{
		u = u + v;
		return u;
	}

	Vector2& operator-=(Vector2& u, const Vector2& v)
	{
		u = u - v;
		return u;
	}

	Vector2& operator*=(Vector2& u, const Vector2& v)
	{
		u = u * v;
		return u;
	}

	Vector2& operator/=(Vector2& u, const Vector2& v)
	{
		u = u / v;
		return u;
	}


	Vector3 operator+(const Vector3& u, const Vector3& v)
	{
		return { u.x + v.x, u.y + v.y, u.z + v.z };
	}

	Vector3 operator-(const Vector3& u, const Vector3& v)
	{
		return { u.x - v.x, u.y - v.y, u.z - v.z };
	}

	Vector3 operator*(const Vector3& u, const Vector3& v)
	{
		return { u.x * v.x, u.y * v.y, u.z * v.z };
	}

	Vector3 operator/(const Vector3& u, const Vector3& v)
	{
		return { u.x / v.x, u.y / v.y, u.z / v.z };
	}

	Vector3 operator-(const Vector3& u)
	{
		return { -u.x, -u.y, -u.z };
	}


	Vector3& operator+=(Vector3& u, const Vector3& v)
	{
		u = u + v;
		return u;
	}

	Vector3& operator-=(Vector3& u, const Vector3& v)
	{
		u = u - v;
		return u;
	}

	Vector3& operator*=(Vector3& u, const Vector3& v)
	{
		u = u * v;
		return u;
	}

	Vector3& operator/=(Vector3& u, const Vector3& v)
	{
		u = u / v;
		return u;
	}


	Vector4 operator+(const Vector4& u, const Vector4& v)
	{
		return { u.x + v.x, u.y + v.y, u.z + v.z, u.w + v.w };
	}

	Vector4 operator-(const Vector4& u, const Vector4& v)
	{
		return { u.x - v.x, u.y - v.y, u.z - v.z, u.w - v.w };
	}

	Vector4 operator*(const Vector4& u, const Vector4& v)
	{
		return { u.x * v.x, u.y * v.y, u.z * v.z, u.w * v.w };
	}

	Vector4 operator/(const Vector4& u, const Vector4& v)
	{
		return { u.x / v.x, u.y / v.y, u.z / v.z, u.w / v.w };
	}

	Vector4 operator-(const Vector4& u)
	{
		return { -u.x, -u.y, -u.z, -u.w };
	}


	Vector4& operator+=(Vector4& u, const Vector4& v)
	{
		u = u + v;
		return u;
	}

	Vector4& operator-=(Vector4& u, const Vector4& v)
	{
		u = u - v;
		return u;
	}

	Vector4& operator*=(Vector4& u, const Vector4& v)
	{
		u = u * v;
		return u;
	}

	Vector4& operator/=(Vector4& u, const Vector4& v)
	{
		u = u / v;
		return u;
	}
}
