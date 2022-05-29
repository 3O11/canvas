#ifndef _CC_MATH_UTILS_H
#define _CC_MATH_UTILS_H

#include "Types.h"

namespace cc
{
    static constexpr Float FloatEps = Float(0.00001);

    Float Clamp(Float value, Float min, Float max);
    Float Sign(Float value);
    bool  Equal(Float v1, Float v2);
}

#endif //_CC_MATH_UTILS_H
