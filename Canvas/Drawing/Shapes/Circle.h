#ifndef _CC_CIRCLE_H
#define _CC_CIRCLE_H

#include "Types.h"
#include "Shape.h"

namespace cc
{
    class Circle : public Shape
    {
    public:
        Circle(Float xCenter, Float yCenter, Float radius);


        void Fill(bool fill);
        void Thickness(Float thickness);

        Float Contribution(Float x, Float y) override;
    private:
        Float m_xCenter;
        Float m_yCenter;
        Float m_radius;
        
        bool  m_fill = false;
        Float m_thickness = 1;
    };
}

#endif //_CC_CIRCLE_H
