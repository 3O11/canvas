#ifndef _CC_CANVAS_H
#define _CC_CANVAS_H

#include "Types.h"
#include "RGB.h"
#include "Image.h"

#include "shape.h"

#include <memory>

namespace cc
{
    class Canvas
    {
    public:
        Canvas(int32_t width = 640, int32_t height = 480, const RGBA& fillColour = {});
        Canvas(Image&& image);

        void Clear(const RGB& clearColour);
        void Draw(std::shared_ptr<Shape> shape, const RGBA& colour);
        void Draw(int32_t x, int32_t y, const RGBA& colour);

        void SetOffset(int32_t x, int32_t y);

        Image& ImageHandle();

    private:
        Image m_internalImage;
        int32_t m_xOffset;
        int32_t m_yOffset;
    };
}

#endif //_CC_CANVAS_H
