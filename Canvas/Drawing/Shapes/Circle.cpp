#include "Circle.h"

#include "Vector.h"

#include <cmath>

namespace cc
{
    Circle::Circle(Float xCenter, Float yCenter, Float radius)
        : m_xCenter(xCenter), m_yCenter(yCenter), m_radius(radius)
    {}

    void Circle::Fill(bool fill)
    {
        m_fill = fill;
    }

    void Circle::Thickness(Float thickness)
    {
        m_thickness = thickness;
    }

    Float Circle::Contribution(Float x, Float y)
    {
        auto dist = Length(Vector2(m_xCenter - x, m_yCenter - y));


        return m_fill ? dist - m_radius < m_thickness : std::abs(dist - m_radius) < m_thickness;
    }
}
