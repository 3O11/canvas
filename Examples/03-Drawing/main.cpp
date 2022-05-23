
#include "RGB.h"
#include "Image.h"
#include "Canvas.h"
#include "Shapes/Circle.h"
#include "Drawing.h"

#include "ImguiWindow.h"

#include <memory>
#include <cmath>

using namespace cc;

Float clamp(Float value, Float min, Float max)
{
    if (value < min) return min;
    if (value > max) return max;

    return value;
}

class ConicSection : public Shape
{
public:
    Float Contribution(Float x, Float y) override
    {
        x *= m_scale;
        y *= m_scale;

        return std::sqrt(std::abs((x * x * m_x2) + (y * y * m_y2) + (x * y * m_xy) + (x * m_x) + (y * m_y) + m_c)) <= m_threshold;
    }

    void SetParameters(Float x2, Float xy, Float y2, Float x, Float y, Float c)
    {
        m_x2 = x2;
        m_xy = xy;
        m_y2 = y2;
        m_x  = x;
        m_y  = y;
        m_c  = c;
    }

    void SetScale(Float scaleMul)
    {
        m_scale = scaleMul;
    }

    void SetThreshold(Float threshold)
    {
        m_threshold = threshold;
    }

private:
    Float m_x2 = 1;
    Float m_xy = 1;
    Float m_y2 = 1;
    Float m_x  = 1;
    Float m_y  = 1;
    Float m_c  = 1;

    Float m_scale;
    Float m_threshold;
};

//#define USE_WINDOW

int main()
{
#ifndef USE_WINDOW
    // This is for use when creating a window isn't possible/desirable

    Canvas c(1024, 1024, {1.0f, 1.0f, 1.0f, 0.0f});
    c.SetOffset(512, 512); // Set the 0,0 coordinate to be the center of the image

    // Draw a circle in the center of the image
    //std::shared_ptr<cc::Circle> circle = std::make_shared<cc::Circle>(0, 0, 120);
    //circle->Fill(true);
    //c.Draw(circle, {1.0f, 0.6f, 0.0f, 0.5f});

    std::shared_ptr<ConicSection> conic_section = std::make_shared<ConicSection>();
    conic_section->SetParameters(52, -72, 73, -280, 290, 325);
    conic_section->SetScale(1 / 128.0f); // Set the scale to draw a meaningful picture
    conic_section->SetThreshold(1);
    c.Draw(conic_section, {1.0f, 0.0f, 0.0f, 1.0f});

    Image& i = c.ImageHandle();
    Image::Save("Image.png", i, cc::ImageType::PNG);

#else

    ImguiWindow window("Conic sections");

    Float x2 = 52, xy = -72, y2 = 73, x = -280, y = 290, c = 325;
    Float min = -1000;
    Float max =  1000;
    Float scale = 1 / 128.0f, scaleMin = 0, scaleMax = 1;
    Float threshold = 1, thresholdMin = 0, thresholdMax = 100;
    std::shared_ptr<ConicSection> conicSection = std::make_shared<ConicSection>();

    uint32_t shader;
    uint32_t texture;

    while (!window.IsClosed())
    {
        window.BeginFrame();

        ImGui::Begin("Options");

        ImGui::SliderScalar("x^2: ", ImGuiDataType_Double, &x2, &min, &max);
        ImGui::SliderScalar("xy: ",  ImGuiDataType_Double, &xy, &min, &max);
        ImGui::SliderScalar("y^2: ", ImGuiDataType_Double, &y2, &min, &max);
        ImGui::SliderScalar("x: ",   ImGuiDataType_Double, &x,  &min, &max);
        ImGui::SliderScalar("y: ",   ImGuiDataType_Double, &y,  &min, &max);
        ImGui::SliderScalar("c: ",   ImGuiDataType_Double, &c,  &min, &max);

        ImGui::SliderScalar("scale: ", ImGuiDataType_Double, &scale, &scaleMin, &scaleMax);
        ImGui::SliderScalar("threshold: ", ImGuiDataType_Double, &threshold, &thresholdMin, &thresholdMax);

        ImGui::End();

        Canvas canvas(window.GetWidth(), window.GetHeight(), {1.0f, 1.0f, 1.0f, 1.0f});
        canvas.SetOffset(window.GetWidth() / 2, window.GetHeight() / 2);

        conicSection->SetParameters(x2, xy, y2, x, y, c);
        conicSection->SetScale(scale);
        conicSection->SetThreshold(threshold);

        canvas.Draw(conicSection, {1.0f, 1.0f, 1.0f, 1.0f});

        // Now I just need to put all the data into the GPU and draw it

        window.EndFrame();
    }

#endif
}