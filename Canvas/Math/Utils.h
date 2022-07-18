#ifndef _CC_MATH_UTILS_H
#define _CC_MATH_UTILS_H

#include "Types.h"

namespace cc
{
    static constexpr Float FloatEps = Float(0.00001);

    inline static constexpr Float Pi    = Float(3.1415926535897932384626433832795028841971693993751058209749445923);
    inline static constexpr Float E     = Float(2.7182818284590452353602874713526624977572470936999595749669676277);
    inline static constexpr Float Phi   = Float(1.6180339887498948482045868343656381177203091798057628621354486227);
    inline static constexpr Float Sqrt2 = Float(1.4142135623730950488016887242096980785696718753769480731766797379);
    inline static constexpr Float Sqrt3 = Float(1.7320508075688772935274463415058723669428052538103806280558069794);

    Float Clamp(Float value, Float min, Float max);
    Float Sign(Float value);
    bool  Equal(Float v1, Float v2);
}

#endif //_CC_MATH_UTILS_H
