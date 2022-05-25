#include "Utils.h"

namespace cc
{
    Float Clamp(Float value, Float min, Float max)
    {
        if (value < min) return min;
        if (value > max) return max;

        return value;
    }
}
