#ifndef __SHAPE_H
#define __SHAPE_H

#include "Types.h"

class Shape
{
public:
    virtual cc::Float Contribution(cc::Float x, cc::Float y) = 0;
    virtual ~Shape() {};
protected:
};

#endif //__SHAPE_H
