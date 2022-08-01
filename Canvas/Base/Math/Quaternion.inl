#include <cmath>

namespace cc
{
    template <typename T>
    inline QuaternionT<T>::QuaternionT()
        : s(0), v(0)
    {}

    template <typename T>
    inline QuaternionT<T>::QuaternionT(T s, const Vector3T<T>& v)
        : s(s), v(v)
    {}

    template <typename T>
    inline QuaternionT<T>::QuaternionT(T s, T i, T j, T k)
        : s(s), v(i, j, k)
    {}

    template <typename T>
    inline QuaternionT<T> QuaternionT<T>::Make(T angle, const Vector3T<T>& axis)
    {
        QuaternionT<T> q;

        q.v = axis.Normalized() * Vector3T<T>(std::sin(angle / 2));
        q.s = std::cos(angle / 2);
        q.Normalize();

        return q;
    }

    template <typename T>
    inline QuaternionT<T>& QuaternionT<T>::Normalize()
    {
        T length = std::sqrt(s * s + v.LengthSquared());

        s /= length;
        v /= Vector3T<T>(length);

        return *this;
    }

    template <typename T>
    inline QuaternionT<T> QuaternionT<T>::Normalized() const
    {
        return QuaternionT<T>(*this).Normalize();
    }

    template <typename T>
    inline QuaternionT<T> QuaternionT<T>::Conjugate() const
    {
        QuaternionT<T> q;
        
        q.s = s;
        q.v = -v;

        return q;
    }

    template <typename T>
    inline Matrix3T<T> QuaternionT<T>::ToMatrix3() const
    {
        Matrix3T<T> m;

        m[0][0] = (s * s) + (v.x * v.x) - (v.y * v.y) - (v.z * v.z);
        m[0][1] = 2 * (v.x * v.y - s * v.z);
        m[0][2] = 2 * (v.x * v.z + s * v.y);

        m[1][0] = 2 * (v.x * v.y + s * v.z);
        m[1][1] = (s * s) - (v.x * v.x) + (v.y * v.y) - (v.z * v.z);
        m[1][2] = 2 * (v.y * v.z - s * v.x);

        m[2][0] = 2 * (v.x * v.z - s * v.y);
        m[2][1] = 2 * (v.y * v.z + s * v.x);
        m[2][2] = (s * s) - (v.x * v.x) - (v.y * v.y) + (v.z * v.z);

        return m;
    }

    template <typename T>
    inline Matrix4T<T> QuaternionT<T>::ToMatrix4() const
    {
        Matrix4T<T> m(1);

        m[0][0] = (s * s) + (v.x * v.x) - (v.y * v.y) - (v.z * v.z);
        m[0][1] = 2 * (v.x * v.y - s * v.z);
        m[0][2] = 2 * (v.x * v.z + s * v.y);

        m[1][0] = 2 * (v.x * v.y + s * v.z);
        m[1][1] = (s * s) - (v.x * v.x) + (v.y * v.y) - (v.z * v.z);
        m[1][2] = 2 * (v.y * v.z - s * v.x);
        
        m[2][0] = 2 * (v.x * v.z - s * v.y);
        m[2][1] = 2 * (v.y * v.z + s * v.x);
        m[2][2] = (s * s) - (v.x * v.x) - (v.y * v.y) + (v.z * v.z);

        return m;
    }

    template <typename T>
    inline Vector3T<T> QuaternionT<T>::Rotate(const Vector3T<T>& u) const
    {
        return ((*this) * QuaternionT<T>(0, u) * Conjugate()).v;
    }

    template <typename T>
    inline Vector4T<T> QuaternionT<T>::Rotate(const Vector4T<T>& u) const
    {
        return { Rotate(Vector3T<T>( u.x, u.y, u.z )), u.w };
    }

    template <typename T>
    inline QuaternionT<T> operator+(const QuaternionT<T>& u, const QuaternionT<T>& v)
    {
        return QuaternionT<T>(u.s + v.s, u.v + v.v);
    }

    template <typename T>
    inline QuaternionT<T> operator-(const QuaternionT<T>& u, const QuaternionT<T>& v)
    {
        return QuaternionT<T>(u.s - v.s, u.v - v.v);
    }

    template <typename T>
    inline QuaternionT<T> operator*(const QuaternionT<T>& u, const QuaternionT<T>& v)
    {   // Hamilton product
        QuaternionT<T> q;

        q.s = u.s * v.s + Vector3T<T>::Dot(u.v, v.v);
        q.v = (u.v * Vector3T<T>(v.s)) + (Vector3T<T>(u.s) * v.v) + Vector3T<T>::Cross(u.v, v.v);

        return q;
    }

    template <typename T>
    inline QuaternionT<T> operator-(const QuaternionT<T>& u)
    {
        QuaternionT<T> q;

        q.s = -u.s;
        q.v = -u.v;

        return q;
    }



    template <typename T>
    inline QuaternionT<T>& operator+=(QuaternionT<T>& u, const QuaternionT<T>& v)
    {
        u.s += v.s;
        u.v += v.v;

        return u;
    }

    template <typename T>
    inline QuaternionT<T>& operator-=(QuaternionT<T>& u, const QuaternionT<T>& v)
    {
        u.s -= v.s;
        u.v -= v.v;

        return u;
    }

    template <typename T>
    inline QuaternionT<T>& operator*=(QuaternionT<T>& u, const QuaternionT<T>& v)
    {
        u.s *= v.s;
        u.v *= v.v;

        return u;
    }


    template <typename T>
    inline QuaternionT<T> operator*(const QuaternionT<T>& u, T s)
    {
        return QuaternionT<T>( u.s * s, u.v * Vector3T<T>(s));
    }

    template <typename T>
    inline QuaternionT<T> operator*(T s, const QuaternionT<T>& u)
    {
        return u * s;
    }


    template <typename T>
    inline QuaternionT<T> Lerp(T value, const QuaternionT<T>& start, const QuaternionT<T>& end)
    {
        value = Clamp(value, T(0), T(1));
        return ((1 - value) * start + value * end).Normalized();
    }

    template <typename T>
    inline QuaternionT<T> Slerp(T value, const QuaternionT<T>& start, const QuaternionT<T>& end)
    {
        // TODO: Something is not quite right here, I'll need to investigate this later.

        value = Clamp(value, T(0), T(1));

        T cos_angle = start.s * end.s + Vector3T<T>::Dot(start.v, end.v);
        T angle = std::acos(cos_angle);
        T sin_angle = 1 - cos_angle * cos_angle; //std::sin(angle);

        return ((std::sin((1 - value) * angle) / sin_angle) * start + (std::sin(value * angle) / sin_angle) * end);
    }
}