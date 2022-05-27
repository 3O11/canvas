#include "ImguiWindow.h"
#include "Window.h"
#include "RGB.h"
#include "Image.h"
#include "Canvas.h"
#include "Shapes/Circle.h"
#include "Drawing.h"
#include "Texture.h"
#include "Shader.h"
#include "Vector.h"
#include "Buffers.h"

#include <memory>
#include <cmath>

using namespace cc;

static const std::string vertexShader = 
R"(
    #version 150

    in vec4 inPos; 
    in vec2 inTex;   

    out vec4 pos;
    out vec2 tex;

    void main()
    {
        pos = inPos;
        tex = inTex;
        gl_Position = inPos;
    }
)";

static const std::string fragmentShader = 
R"(
    #version 150

    in vec4 pos;
    in vec2 tex;

    uniform sampler2D u_texture;

    out vec4 outColour;

    void main()
    {
        outColour = texture2D(u_texture, tex);
    }
)";

struct Vertex
{
    Vector3 pos;
    Vector2 tex;
};

static const std::vector<Vertex> points =
{
    {{-1.0f, -1.0f, 0.0f}, { 0.0f, 0.0f }},
    {{ 1.0f, -1.0f, 0.0f}, { 1.0f, 0.0f }},
    {{ 1.0f,  1.0f, 0.0f}, { 1.0f, 1.0f }},
    {{-1.0f,  1.0f, 0.0f}, { 0.0f, 1.0f }},
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

    std::string DetermineType()
    {

    }
private:
    Float m_x2 = 1;
    Float m_xy = 1;
    Float m_y2 = 1;
    Float m_x  = 1;
    Float m_y  = 1;
    Float m_c  = 1;

    Float m_scale = Float(1) / Float(128);
    Float m_threshold = Float(1);
};

#define USE_WINDOW

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

    ImguiWindow window("Conic sections", 1024, 1024);
    window.SetClearColour({ 1.0f, 0.0f, 0.0f, 1.0f });

    Float x2 = 52, xy = -72, y2 = 73, x = -280, y = 290, c = 325;
    Float min = -1000;
    Float max = 1000;
    Float scale = 1 / 128.0f, scaleMin = 0, scaleMax = 0.5f;
    Float threshold = 1, thresholdMin = 0, thresholdMax = 10;
    std::shared_ptr<ConicSection> conicSection = std::make_shared<ConicSection>();

    Shader shader(vertexShader, fragmentShader);

    VertexArray vao;
    VertexBuffer vbo(&points[0], 4, sizeof(Vertex));
    ElementBuffer ebo(&indices[0], 6);

    vbo.GetLayout().AddElement<Float>(3);
    vbo.GetLayout().AddElement<Float>(2);
    vao.AddBuffer(vbo);

    while (!window.IsClosed())
    {
        window.BeginFrame();

        ImGui::Begin("Options");

        ImGui::SliderScalar("x^2", ImGuiDataType_Float, &x2, &min, &max, "%.1f x^2");
        ImGui::SliderScalar("xy", ImGuiDataType_Float, &xy, &min, &max, "%.10f xy");
        ImGui::SliderScalar("y^2", ImGuiDataType_Float, &y2, &min, &max, "%.10f y^2");
        ImGui::SliderScalar("x", ImGuiDataType_Float, &x, &min, &max, "%.10f x");
        ImGui::SliderScalar("y", ImGuiDataType_Float, &y, &min, &max, "%.10f y");
        ImGui::SliderScalar("c", ImGuiDataType_Float, &c, &min, &max, "%.10f");

        ImGui::SliderScalar("scale", ImGuiDataType_Float, &scale, &scaleMin, &scaleMax, "%.10f scale");
        ImGui::SliderScalar("threshold (line thickness/intersecting \"plane\" thickness)", ImGuiDataType_Float, &threshold, &thresholdMin, &thresholdMax, "%.10f threshold");

        ImGui::End();

        Canvas canvas(window.GetWidth(), window.GetHeight(), { 1.0f, 1.0f, 1.0f, 1.0f });
        canvas.SetOffset(window.GetWidth() / 2, window.GetHeight() / 2);

        conicSection->SetParameters(x2, xy, y2, x, y, c);
        conicSection->SetScale(scale);
        conicSection->SetThreshold(threshold);

        canvas.Clear({ 1.0f, 1.0f, 1.0f });
        canvas.Draw(conicSection, { 1.0f, 0.0f, 0.0f, 1.0f });

        Texture tex(canvas.ImageHandle());
        shader.Bind();
        tex.Bind();
        shader.SetUniform1i("u_texture", 0);

        vao.Bind();
        ebo.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        window.EndFrame();
    }

#endif
}