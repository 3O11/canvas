#include <cmath>

namespace cc
{
    template <typename T>
    inline Vector2T<T>::Vector2T()
		: x(0.0), y(0.0)
	{}

	template <typename T>
    inline Vector2T<T>::Vector2T(T val)
		: x(val), y(val)
	{}

	template <typename T>
    inline Vector2T<T>::Vector2T(T x, T y)
		: x(x), y(y)
	{}

	template <typename T>
    inline T& Vector2T<T>::operator[](size_t index)
	{
		if (index == 0) return x;
		return y;
	}

	template <typename T>
    inline const T& Vector2T<T>::operator[](size_t index) const
	{
		if (index == 0) return x;
		return y;
	}

	template <typename T>
    inline T Vector2T<T>::Dot(const Vector2T& u, const Vector2T& v)
	{
		return u.x * v.x + u.y * v.y;
	}

	template <typename T>
    inline T Vector2T<T>::LengthSquared()
	{
		return Dot(*this, *this);
	}

	template <typename T>
    inline T Vector2T<T>::Length()
	{
		return std::sqrt(LengthSquared());
	}

	template <typename T>
    inline Vector2T<T>& Vector2T<T>::Normalize()
	{
		T length = Length();
		x /= length;
		y /= length;

		return *this;
	}

	template <typename T>
    inline Vector2T<T> Vector2T<T>::Normalized() const
	{
        auto normalized = *this;
		normalized.Normalize();
		return normalized;
	}



    template <typename T>
    inline Vector3T<T>::Vector3T()
		: x(0.0), y(0.0), z(0.0)
	{}

	template <typename T>
    inline Vector3T<T>::Vector3T(T val)
		: x(val), y(val), z(val)
	{}

	template <typename T>
    inline Vector3T<T>::Vector3T(T x, T y, T z)
		: x(x), y(y), z(z)
	{}

	template <typename T>
    inline Vector3T<T>::Vector3T(const Vector2T<T>& vec)
		: x(vec.x), y(vec.y), z(0.0)
	{}

	template <typename T>
    inline T& Vector3T<T>::operator[](size_t index)
	{
		if (index == 0) return x;
		if (index == 1) return y;
		return z;
	}

	template <typename T>
    inline const T& Vector3T<T>::operator[](size_t index) const
	{
		if (index == 0) return x;
		if (index == 1) return y;
		return z;
	}

	template <typename T>
    inline T Vector3T<T>::Dot(const Vector3T& u, const Vector3T& v)
	{
		return u.x * v.x + u.y * v.y + u.z * v.z;
	}

	template <typename T>
    inline T Vector3T<T>::LengthSquared()
	{
		return Dot(*this, *this);
	}

	template <typename T>
    inline T Vector3T<T>::Length()
	{
		return std::sqrt(LengthSquared());
	}

	template <typename T>
    inline Vector3T<T>& Vector3T<T>::Normalize()
	{
		T length = Length();
		x /= length;
		y /= length;
		z /= length;

		return *this;
	}

	template <typename T>
    inline Vector3T<T> Vector3T<T>::Normalized() const
	{
        auto normalized = *this;
		normalized.Normalize();
		return normalized;
	}

	template <typename T>
    inline Vector3T<T> Vector3T<T>::Cross(const Vector3T& u, const Vector3T& v)
	{
		Vector3T c;

		c.x = u.y * v.z - u.z * v.y;
		c.y = u.z * v.x - u.x * v.z;
		c.z = u.x * v.y - u.y * v.x;

		return c;
	}



    template <typename T>
    inline Vector4T<T>::Vector4T()
		: x(0.0), y(0.0), z(0.0), w(0.0)
	{}

	template <typename T>
    inline Vector4T<T>::Vector4T(T val)
		: x(val), y(val), z(val), w(val)
	{}

	template <typename T>
    inline Vector4T<T>::Vector4T(T x, T y, T z)
		: x(x), y(y), z(z), w(1.0)
	{}

	template <typename T>
    inline Vector4T<T>::Vector4T(T x, T y, T z, T w)
		: x(x), y(y), z(z), w(w)
	{}

	template <typename T>
    inline Vector4T<T>::Vector4T(const Vector3T<T>& vec)
		: x(vec.x), y(vec.y), z(vec.z), w(1.0)
	{}

	template <typename T>
    inline Vector4T<T>::Vector4T(const Vector3T<T>& vec, T w)
		: x(vec.x), y(vec.y), z(vec.z), w(w)
	{}

	template <typename T>
    inline T& Vector4T<T>::operator[](size_t index)
	{
		if (index == 0) return x;
		if (index == 1) return y;
		if (index == 2) return z;
		return w;
	}

	template <typename T>
    inline const T& Vector4T<T>::operator[](size_t index) const
	{
		if (index == 0) return x;
		if (index == 1) return y;
		if (index == 2) return z;
		return w;
	}

	template <typename T>
    inline T Vector4T<T>::Dot(const Vector4T<T>& u, const Vector4T<T>& v)
	{
		return u.x * v.x + u.y * v.y + u.z * v.z + u.w * v.w;
	}

	template <typename T>
    inline T Vector4T<T>::LengthSquared()
	{
		return Dot(*this, *this);
	}

	template <typename T>
    inline T Vector4T<T>::Length()
	{
		return std::sqrt(LengthSquared());
	}

	template <typename T>
    inline Vector4T<T>& Vector4T<T>::Normalize()
	{
		T length = Length();
		x /= length;
		y /= length;
		z /= length;
		w /= length;

		return *this;
	}

	template <typename T>
    inline Vector4T<T> Vector4T<T>::Normalized() const
	{
        auto normalized = *this;
		normalized.Normalize();
		return normalized;
	}



    template <typename T>
    inline Vector2T<T> operator+(const Vector2T<T>& u, const Vector2T<T>& v)
	{
		return {u.x + v.x, u.y + v.y};
	}

	template <typename T>
    inline Vector2T<T> operator-(const Vector2T<T>& u, const Vector2T<T>& v)
	{
		return { u.x - v.x, u.y - v.y };
	}

	template <typename T>
    inline Vector2T<T> operator*(const Vector2T<T>& u, const Vector2T<T>& v)
	{
		return { u.x * v.x, u.y * v.y };
	}

	template <typename T>
    inline Vector2T<T> operator/(const Vector2T<T>& u, const Vector2T<T>& v)
	{
		return { u.x / v.x, u.y / v.y };
	}

	template <typename T>
    inline Vector2T<T> operator-(const Vector2T<T>& u)
	{
		return { -u.x, -u.y };
	}


	template <typename T>
    inline Vector2T<T>& operator+=(Vector2T<T>& u, const Vector2T<T>& v)
	{
		u = u + v;
		return u;
	}

	template <typename T>
    inline Vector2T<T>& operator-=(Vector2T<T>& u, const Vector2T<T>& v)
	{
		u = u - v;
		return u;
	}

	template <typename T>
    inline Vector2T<T>& operator*=(Vector2T<T>& u, const Vector2T<T>& v)
	{
		u = u * v;
		return u;
	}

	template <typename T>
    inline Vector2T<T>& operator/=(Vector2T<T>& u, const Vector2T<T>& v)
	{
		u = u / v;
		return u;
	}


	template <typename T>
    inline Vector3T<T> operator+(const Vector3T<T>& u, const Vector3T<T>& v)
	{
		return { u.x + v.x, u.y + v.y, u.z + v.z };
	}

	template <typename T>
    inline Vector3T<T> operator-(const Vector3T<T>& u, const Vector3T<T>& v)
	{
		return { u.x - v.x, u.y - v.y, u.z - v.z };
	}

	template <typename T>
    inline Vector3T<T> operator*(const Vector3T<T>& u, const Vector3T<T>& v)
	{
		return { u.x * v.x, u.y * v.y, u.z * v.z };
	}

	template <typename T>
    inline Vector3T<T> operator/(const Vector3T<T>& u, const Vector3T<T>& v)
	{
		return { u.x / v.x, u.y / v.y, u.z / v.z };
	}

	template <typename T>
    inline Vector3T<T> operator-(const Vector3T<T>& u)
	{
		return { -u.x, -u.y, -u.z };
	}


	template <typename T>
    inline Vector3T<T>& operator+=(Vector3T<T>& u, const Vector3T<T>& v)
	{
		u = u + v;
		return u;
	}

	template <typename T>
    inline Vector3T<T>& operator-=(Vector3T<T>& u, const Vector3T<T>& v)
	{
		u = u - v;
		return u;
	}

	template <typename T>
    inline Vector3T<T>& operator*=(Vector3T<T>& u, const Vector3T<T>& v)
	{
		u = u * v;
		return u;
	}

	template <typename T>
    inline Vector3T<T>& operator/=(Vector3T<T>& u, const Vector3T<T>& v)
	{
		u = u / v;
		return u;
	}


	template <typename T>
    inline Vector4T<T> operator+(const Vector4T<T>& u, const Vector4T<T>& v)
	{
		return { u.x + v.x, u.y + v.y, u.z + v.z, u.w + v.w };
	}

	template <typename T>
    inline Vector4T<T> operator-(const Vector4T<T>& u, const Vector4T<T>& v)
	{
		return { u.x - v.x, u.y - v.y, u.z - v.z, u.w - v.w };
	}

	template <typename T>
    inline Vector4T<T> operator*(const Vector4T<T>& u, const Vector4T<T>& v)
	{
		return { u.x * v.x, u.y * v.y, u.z * v.z, u.w * v.w };
	}

	template <typename T>
    inline Vector4T<T> operator/(const Vector4T<T>& u, const Vector4T<T>& v)
	{
		return { u.x / v.x, u.y / v.y, u.z / v.z, u.w / v.w };
	}

	template <typename T>
    inline Vector4T<T> operator-(const Vector4T<T>& u)
	{
		return { -u.x, -u.y, -u.z, -u.w };
	}


	template <typename T>
    inline Vector4T<T>& operator+=(Vector4T<T>& u, const Vector4T<T>& v)
	{
		u = u + v;
		return u;
	}

	template <typename T>
    inline Vector4T<T>& operator-=(Vector4T<T>& u, const Vector4T<T>& v)
	{
		u = u - v;
		return u;
	}

	template <typename T>
    inline Vector4T<T>& operator*=(Vector4T<T>& u, const Vector4T<T>& v)
	{
		u = u * v;
		return u;
	}

	template <typename T>
    inline Vector4T<T>& operator/=(Vector4T<T>& u, const Vector4T<T>& v)
	{
		u = u / v;
		return u;
	}
}