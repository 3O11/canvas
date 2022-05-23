#include "Canvas.h"

#include <cmath>

namespace cc
{
    Canvas::Canvas(int32_t width, int32_t height, const RGBA& fillColour)
        : m_internalImage(width, height, fillColour), m_xOffset(0), m_yOffset(0)
    {}

    Canvas::Canvas(Image&& image)
        : m_internalImage(std::move(image)), m_xOffset(0), m_yOffset(0)
    {}

    void Canvas::Clear(const RGB& clearColour)
    {
        m_internalImage.Fill(clearColour);
    }

    void Canvas::Draw(std::shared_ptr<Shape> shape, const RGBA& colour)
    {
        // TODO: Add bounds so that it's not necessary to traverse the entire
        // image for every Draw.

        for (int32_t y = 0; y < m_internalImage.Height(); y++)
        {
            for (int32_t x = 0; x < m_internalImage.Width(); x++)
            {
                RGBA contribution = colour;
                contribution.a *= shape->Contribution(x - m_xOffset, y - m_yOffset);
                Draw(x + m_xOffset, y + m_yOffset, contribution);
            }
        }
    }

    void Canvas::Draw(int32_t x, int32_t y, const RGBA& colour)
    {
        RGBA newColour = m_internalImage(x - m_xOffset, y - m_yOffset);
        newColour.r = newColour.r * (1 - colour.a) + colour.r * colour.a;
        newColour.g = newColour.g * (1 - colour.a) + colour.g * colour.a;
        newColour.b = newColour.b * (1 - colour.a) + colour.b * colour.a;
        newColour.a = std::max(newColour.a, colour.a);

        m_internalImage(x - m_xOffset, y - m_yOffset) = newColour;
    }

    void Canvas::SetOffset(int32_t x, int32_t y)
    {
        m_xOffset = x;
        m_yOffset = y;
    }

    Image& Canvas::ImageHandle()
    {
        return m_internalImage;
    }
}
