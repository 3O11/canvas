#ifndef _CC_TRANSFORMS_H
#define _CC_TRANSFORMS_H


// This is temporary, needs to be removed later
#include "CanvasMath.h"

namespace cc
{
    namespace transform
    {
        Matrix4 Scale       (const Matrix4& mat, Float scale);
        Matrix4 Scale       (const Matrix4& mat, const Vector3& scales);

        Matrix4 Translate   (const Matrix4& mat, const Vector3& vector);
        
        Matrix4 RotateX     (const Matrix4& mat, Float angle);
        Matrix4 RotateY     (const Matrix4& mat, Float angle);
        Matrix4 RotateZ     (const Matrix4& mat, Float angle);

        Matrix4 Perspective (Float aspectRatio, Float fov, Float near, Float far);
    }
}

#endif //_CC_TRANSFORMS_H
