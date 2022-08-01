#ifndef __CANVAS_H
#define __CANVAS_H

#include "Types.h"
#include "RGB.h"
#include "Image.h"

#include "shape.h"

#include <memory>

class Canvas
{
public:
    Canvas(int32_t width = 640, int32_t height = 480, const cc::RGBA& fillColour = {});
    Canvas(cc::Image&& image);

    void Clear(const cc::RGB& clearColour);
    void Draw(std::shared_ptr<Shape> shape, const cc::RGBA& colour);
    void Draw(int32_t x, int32_t y, const cc::RGBA& colour);

    void SetOffset(int32_t x, int32_t y);

    cc::Image& ImageHandle();

private:
    cc::Image m_internalImage;
    int32_t m_xOffset;
    int32_t m_yOffset;
};

#endif //__CANVAS_H
