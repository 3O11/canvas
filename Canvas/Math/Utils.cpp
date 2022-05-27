#include "Utils.h"

namespace cc
{
    Float Clamp(Float value, Float min, Float max)
    {
        if (value < min) return min;
        if (value > max) return max;

        return value;
    }

    Float Sign(Float value)
    {
        return Float((value > 0) - (value < 0));
    }
}
