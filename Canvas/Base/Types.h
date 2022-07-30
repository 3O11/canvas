#ifndef _CC_TYPES_H
#define _CC_TYPES_H

#include <cstdint>
#include <cstddef>

#include "Math/Vector.h"
#include "Math/Matrix.h"

namespace cc
{
	using Float = float;

	using Vector2 = Vector2T<float>;
	using Vector3 = Vector3T<float>;
	using Vector4 = Vector4T<float>;
	
	using Matrix3 = Matrix3T<float>;
	using Matrix4 = Matrix4T<float>;
}

#endif //_CC_TYPES_H
