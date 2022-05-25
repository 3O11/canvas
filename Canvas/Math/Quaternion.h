#ifndef _CC_QUATERNION_H
#define _CC_QUATERNION_H

#include "Types.h"
#include "Vector.h"
#include "Matrix.h"

namespace cc
{
    struct Quaternion final
    {
        explicit Quaternion();
        explicit Quaternion(Float s, const Vector3& v);
        explicit Quaternion(Float s, Float i, Float j, Float k);

        static Quaternion Make(Float angle, const Vector3& axis);

        Quaternion& Normalize();
        Quaternion Normalized() const;

        Quaternion Conjugate() const;

        Matrix3 ToMatrix3() const;
        Matrix4 ToMatrix4() const;

        Vector3 Rotate(const Vector3& u) const;
        Vector4 Rotate(const Vector4& u) const;

        Float s;
        Vector3 v;
    };

    Quaternion operator+(const Quaternion& u, const Quaternion& v);
    Quaternion operator-(const Quaternion& u, const Quaternion& v);
    Quaternion operator*(const Quaternion& u, const Quaternion& v);
    Quaternion operator-(const Quaternion& u);

    Quaternion& operator+=(Quaternion& u, const Quaternion& v);
    Quaternion& operator-=(Quaternion& u, const Quaternion& v);
    Quaternion& operator*=(Quaternion& u, const Quaternion& v);

    Quaternion operator*(const Quaternion& u, Float s);
    Quaternion operator*(Float s, const Quaternion& u);

    Quaternion Lerp(Float value, const Quaternion& start, const Quaternion& end);
    Quaternion Slerp(Float value, const Quaternion& start, const Quaternion& end);
}

#endif //_CC_QUATERNION_H
