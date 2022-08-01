#ifndef _CC_QUATERNION_H
#define _CC_QUATERNION_H

#include "Types.h"
#include "Vector.h"
#include "Matrix.h"
#include "Utils.h"

namespace cc
{
    template <typename T>
    struct QuaternionT final
    {
        explicit QuaternionT();
        explicit QuaternionT(T s, const Vector3T<T>& v);
        explicit QuaternionT(T s, T i, T j, T k);

        static QuaternionT<T> Make(T angle, const Vector3T<T>& axis);

        QuaternionT<T>& Normalize();
        QuaternionT<T> Normalized() const;

        QuaternionT<T> Conjugate() const;

        Matrix3T<T> ToMatrix3() const;
        Matrix4T<T> ToMatrix4() const;

        Vector3T<T> Rotate(const Vector3T<T>& u) const;
        Vector4T<T> Rotate(const Vector4T<T>& u) const;

        T s;
        Vector3T<T> v;
    };

    template <typename T>
    QuaternionT<T> operator+(const QuaternionT<T>& u, const QuaternionT<T>& v);
    template <typename T>
    QuaternionT<T> operator-(const QuaternionT<T>& u, const QuaternionT<T>& v);
    template <typename T>
    QuaternionT<T> operator*(const QuaternionT<T>& u, const QuaternionT<T>& v);
    template <typename T>
    QuaternionT<T> operator-(const QuaternionT<T>& u);

    template <typename T>
    QuaternionT<T>& operator+=(QuaternionT<T>& u, const QuaternionT<T>& v);
    template <typename T>
    QuaternionT<T>& operator-=(QuaternionT<T>& u, const QuaternionT<T>& v);
    template <typename T>
    QuaternionT<T>& operator*=(QuaternionT<T>& u, const QuaternionT<T>& v);

    template <typename T>
    QuaternionT<T> operator*(const QuaternionT<T>& u, T s);
    template <typename T>
    QuaternionT<T> operator*(T s, const QuaternionT<T>& u);

    template <typename T>
    QuaternionT<T> Lerp(T value, const QuaternionT<T>& start, const QuaternionT<T>& end);
    template <typename T>
    QuaternionT<T> Slerp(T value, const QuaternionT<T>& start, const QuaternionT<T>& end);
}

#include "Quaternion.inl"

#endif //_CC_QUATERNION_H
