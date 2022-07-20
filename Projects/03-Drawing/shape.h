#ifndef _CC_SHAPE_H
#define _CC_SHAPE_H

#include "Types.h"

namespace cc
{
    class Shape
    {
    public:
        virtual Float Contribution(Float x, Float y) = 0;
        virtual ~Shape() {};
    protected:
    };
}

#endif //_CC_SHAPE_H
