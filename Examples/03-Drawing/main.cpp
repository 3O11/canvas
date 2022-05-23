#include "ImguiWindow.h"
#include "RGB.h"
#include "Image.h"
#include "Canvas.h"
#include "Shapes/Circle.h"
#include "Drawing.h"
#include "Texture.h"
#include "Shader.h"
#include "Vector.h"

#include <memory>
#include <cmath>

using namespace cc;

static const std::string vertexShader = 
R"(
    #version 330

    in vec4 inPos;
    in vec2 inTex;

    out vec4 outPos;
    out vec2 outTex;

    void main()
    {
        outPos = inPos;
        outTex = inTex;
    }
)";

static const std::string fragmentShader = 
R"(
    #version 330

    in vec4 inPos;
    in vec2 inTex;

    out vec4 colour;

    uniform sampler2D u_texture;

    void main()
    {
        colour = texture(u_texture, inTex);

        if (colour.a < 0.5) discard;
    }
)";

static const std::vector<Vector4> points =
{
    {0.0f, 0.0f, -1.0f, 1.0f},
    {1.0f, 0.0f, -1.0f, 1.0f},
    {1.0f, 1.0f, -1.0f, 1.0f},
    {0.0f, 1.0f, -1.0f, 1.0f},
};

static const std::vector<int32_t> indices =
{
    0, 1, 2,
    0, 2, 3,
};

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

    while (!window.IsClosed())
    {
        window.BeginFrame();

        ImGui::Begin("Options");

        ImGui::SliderScalar("", ImGuiDataType_Double, &x2, &min, &max, "%.10f x^2");
        ImGui::SliderScalar("", ImGuiDataType_Double, &xy, &min, &max, "%.10f xy");
        ImGui::SliderScalar("", ImGuiDataType_Double, &y2, &min, &max, "%.10f y^2");
        ImGui::SliderScalar("", ImGuiDataType_Double, &x,  &min, &max, "%.10f x");
        ImGui::SliderScalar("", ImGuiDataType_Double, &y,  &min, &max, "%.10f y");
        ImGui::SliderScalar("", ImGuiDataType_Double, &c,  &min, &max, "%.10f c");

        ImGui::SliderScalar("scale: ", ImGuiDataType_Double, &scale, &scaleMin, &scaleMax);
        ImGui::SliderScalar("threshold: ", ImGuiDataType_Double, &threshold, &thresholdMin, &thresholdMax);

        ImGui::End();

        Canvas canvas(window.GetWidth(), window.GetHeight(), {1.0f, 1.0f, 1.0f, 1.0f});
        canvas.SetOffset(window.GetWidth() / 2, window.GetHeight() / 2);

        conicSection->SetParameters(x2, xy, y2, x, y, c);
        conicSection->SetScale(scale);
        conicSection->SetThreshold(threshold);

        canvas.Draw(conicSection, {1.0f, 1.0f, 1.0f, 1.0f});

        Texture tex(canvas.ImageHandle());

        uint32_t vbo, ibo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(Vector4), points.data(), GL_STATIC_DRAW);

        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int32_t), indices.data(), GL_STATIC_DRAW);

        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);

        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ibo);

        window.EndFrame();
    }

#endif
}