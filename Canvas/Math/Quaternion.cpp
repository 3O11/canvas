#include "Quaternion.h"

#include "Utils.h"

#include <cmath>

namespace cc
{
    Quaternion::Quaternion()
        : s(0), v(0)
    {}

    Quaternion::Quaternion(Float s, const Vector3& v)
        : s(s), v(v)
    {}

    Quaternion::Quaternion(Float s, Float i, Float j, Float k)
        : s(s), v(i, j, k)
    {}

    Quaternion Quaternion::Make(Float angle, const Vector3& axis)
    {
        Quaternion q;

        q.v = axis.Normalized() * std::sin(angle / 2);
        q.s = std::cos(angle / 2);
        q.Normalize();

        return q;
    }

    Quaternion& Quaternion::Normalize()
    {
        Float length = std::sqrt(s * s + v.LengthSquared());

        s /= length;
        v /= length;

        return *this;
    }

    Quaternion Quaternion::Normalized() const
    {
        return Quaternion(*this).Normalize();
    }

    Quaternion Quaternion::Conjugate() const
    {
        Quaternion q;
        
        q.s = s;
        q.v = -v;

        return q;
    }

    Matrix3 Quaternion::ToMatrix3() const
    {
        Matrix3 m;

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

    Matrix4 Quaternion::ToMatrix4() const
    {
        Matrix4 m(1);

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

    Vector3 Quaternion::Rotate(const Vector3& u) const
    {
        return ((*this) * Quaternion(0, u) * Conjugate()).v;
    }

    Vector4 Quaternion::Rotate(const Vector4& u) const
    {
        return { Rotate(Vector3( u.x, u.y, u.z )), u.w };
    }

    Quaternion operator+(const Quaternion& u, const Quaternion& v)
    {
        return Quaternion(u.s + v.s, u.v + v.v);
    }

    Quaternion operator-(const Quaternion& u, const Quaternion& v)
    {
        return Quaternion(u.s - v.s, u.v - v.v);
    }

    Quaternion operator*(const Quaternion& u, const Quaternion& v)
    {   // Hamilton product
        Quaternion q;

        q.s = u.s * v.s + Vector3::Dot(u.v, v.v);
        q.v = (u.v * v.s) + (u.s * v.v) + Vector3::Cross(u.v, v.v);

        return q;
    }

    Quaternion operator-(const Quaternion& u)
    {
        Quaternion q;

        q.s = -u.s;
        q.v = -u.v;

        return q;
    }


    Quaternion& operator+=(Quaternion& u, const Quaternion& v)
    {
        u.s += v.s;
        u.v += v.v;

        return u;
    }

    Quaternion& operator-=(Quaternion& u, const Quaternion& v)
    {
        u.s -= v.s;
        u.v -= v.v;

        return u;
    }

    Quaternion& operator*=(Quaternion& u, const Quaternion& v)
    {
        u.s *= v.s;
        u.v *= v.v;

        return u;
    }


    Quaternion operator*(const Quaternion& u, Float s)
    {
        return Quaternion( u.s * s, u.v * s );
    }

    Quaternion operator*(Float s, const Quaternion& u)
    {
        return u * s;
    }


    Quaternion Lerp(Float value, const Quaternion& start, const Quaternion& end)
    {
        value = Clamp(value, Float(0), Float(1));
        return ((1 - value) * start + value * end).Normalized();
    }

    Quaternion Slerp(Float value, const Quaternion& start, const Quaternion& end)
    {
        value = Clamp(value, Float(0), Float(1));

        Float cos_angle = start.s * end.s + Vector3::Dot(start.v, end.v);
        Float angle = std::acos(cos_angle);
        Float sin_angle = 1 - cos_angle * cos_angle; //std::sin(angle);

        return ((std::sin((1 - value) * angle) / sin_angle) * start + (std::sin(value * angle) / sin_angle) * end);
    }
}
