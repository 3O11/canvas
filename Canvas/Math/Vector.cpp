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


	Float Dot(const Vector2& u, const Vector2& v)
	{
		return u.x * v.x + u.y * v.y;
	}

	Float Dot(const Vector3& u, const Vector3& v)
	{
		return u.x * v.x + u.y * v.y + u.z * v.z;
	}

	Float Dot(const Vector4& u, const Vector4& v)
	{
		return u.x * v.x + u.y * v.y + u.z * v.z + u.w * v.w;
	}


	Float LengthSquared(const Vector2& u, const Vector2& v)
	{
		return Dot(u, v);
	}

	Float LengthSquared(const Vector3& u, const Vector3& v)
	{
		return Dot(u, v);
	}

	Float LengthSquared(const Vector4& u, const Vector4& v)
	{
		return Dot(u, v);
	}


	Float Length(const Vector2& u, const Vector2& v)
	{
		return std::sqrt(LengthSquared(u, v));
	}

	Float Length(const Vector3& u, const Vector3& v)
	{
		return std::sqrt(LengthSquared(u, v));
	}

	Float Length(const Vector4& u, const Vector4& v)
	{
		return std::sqrt(LengthSquared(u, v));
	}
}
