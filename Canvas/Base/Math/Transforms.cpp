#include "Transforms.h"

#include <cmath>

namespace cc
{
    namespace transform
    {
        Matrix4 Scale (const Matrix4& mat, Float scale)
        {
            Matrix4 newTransform = mat;
            for (size_t i = 0; i < 3; i++)
            {
                for (size_t j = 0; j < 3; j++)
                {
                    newTransform[i][j] *= scale;
                }
                
            }
            return newTransform;
        }

        Matrix4 Scale (const Matrix4& mat, const Vector3& scales)
        {
            Matrix4 newTransform = mat;
            for (size_t i = 0; i < 3; i++)
            {
                for (size_t j = 0; j < 3; j++)
                {
                    newTransform[i][j] *= scales[i];
                }
                
            }
            return newTransform;
        }

        Matrix4 Translate (const Matrix4& mat, const Vector3& vector)
        {
            Matrix4 newTransform = mat;
            for (size_t i = 0; i < 3; i++)
            {
                newTransform[i][3] += vector[i];
            }
            return newTransform;
        }
        
        Matrix4 RotateX (const Matrix4& mat, Float angle)
        {
            Matrix4 rotation = Matrix4
            (
                { 1,               0,                0, 0 },
                { 0, std::cos(angle), -std::sin(angle), 0 },
                { 0, std::sin(angle),  std::cos(angle), 0 },
                { 0,               0,                0, 1 }
            );

            return rotation * mat;
        }

        Matrix4 RotateY (const Matrix4& mat, Float angle)
        {
            Matrix4 rotation = Matrix4
            (
                {  std::cos(angle), 0,  std::sin(angle), 0 },
                {               0, 1,                0, 0 },
                { -std::sin(angle), 0,  std::cos(angle), 0 },
                {               0, 0,                0, 1 }
            );

            return rotation * mat;
        }

        Matrix4 RotateZ (const Matrix4& mat, Float angle)
        {
            Matrix4 rotation = Matrix4
            (
                { std::cos(angle), -std::sin(angle), 0, 0 },
                { std::sin(angle),  std::cos(angle), 0, 0 },
                {               0,                0, 1, 0 },
                {               0,                0, 0, 1 }
            );

            return rotation * mat;
        }

        Matrix4 Perspective(Float aspectRatio, Float fov, Float near, Float far)
        {
            Float tanHalfFov = std::tan(fov / 2);

            Matrix4 projection;

            projection[0][0] = Float(1) / (aspectRatio * tanHalfFov);
            projection[1][1] = Float(1) / (tanHalfFov);
            projection[2][2] = -(far + near) / (far - near);
            projection[3][2] = -Float(1);
            projection[2][3] = -(Float(2) * far * near) / (far - near);

            return projection;
        }
    }
}
