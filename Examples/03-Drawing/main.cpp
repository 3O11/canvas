// The include situation is already very messy, I'll need to do something
// about it soon.
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
#include "Utils.h"

#include <memory>
#include <cmath>

using namespace cc;

static const std::string vertexShader = 
R"(
    #version 330

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
    #version 330

    in vec4 pos;
    in vec2 tex;

    uniform sampler2D uTexture;

    out vec4 outColour;

    void main()
    {
        outColour = texture2D(uTexture, tex);
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
        x /= m_scale;
        y /= m_scale;

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

    Float Eccentricity()
    {
        Float sign = Sign(m_c * (m_xy * m_xy - 4 * m_x2 * m_y2) + (m_x2 * m_y * m_y - m_xy * m_x * m_y + m_y2 * m_x * m_x));
        Float comp = std::sqrt((m_x2 - m_y2) * (m_x2 - m_y2) + m_xy * m_xy);
        return std::sqrt((2 * comp) / (sign * (m_x2 + m_y2) + comp));
    }

    std::string DetermineType()
    {
        Float disc = (m_xy * m_xy) - (4 * m_x2 * m_y2);

        if (std::abs(m_x2) <= FloatEps && std::abs(m_y2) <= FloatEps && std::abs(m_xy) <= FloatEps)
        {
            return "Linear (Not a Conic)";
        }

        if (std::abs(disc) <= FloatEps)
        {
            return "Parabola";
        }

        if (disc > 0)
        {
            if (std::abs(m_x2 + m_y2) <= FloatEps)
            {
                return "Rectangular hyperbola";
            }

            return "Hyperbola";
        }
        else
        {
            if (std::abs(m_x2 - m_y2) <= FloatEps && std::abs(m_xy) <= FloatEps)
            {
                if (std::abs(m_x) <= FloatEps && std::abs(m_y) <= FloatEps)
                {
                    return "Point";
                }

                return "Circle";
            }
            else
            {
                return "Ellipse";
            }
        }
    }

    std::string Center()
    {
        return "WIP";

        Float ecc = Eccentricity();
        if (ecc <= FloatEps)
        { // Circle case
            
        }
        else if (std::abs(1.0f - ecc) <= FloatEps)
        { // Parabola case

        }
        else if (ecc > 0.0f && ecc < 1.0f)
        { // Ellipse case

        }
        else
        { // Hyperbola case

        }
    }

    std::string Radii()
    {
        return "WIP";
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

    ImguiWindow window("Conic sections", 640, 480);
    window.SetClearColour({ 1.0f, 0.0f, 0.0f, 1.0f });

    Float x2 = 52, xy = -72, y2 = 73, x = -280, y = 290, c = 325;
    Float min = -1000;
    Float max = 1000;
    Float scale = 128.0f;
    Float threshold = 1;
    std::shared_ptr<ConicSection> conicSection = std::make_shared<ConicSection>();

    Shader shader(vertexShader, fragmentShader);
    Texture tex(Image(640, 480, {1.0f, 1.0f, 1.0f, 1.0f}));

    bool Updated = true;

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

        ImGui::Text("Current conic section: %s, Eccentricity: %.4f", conicSection->DetermineType().c_str(), conicSection->Eccentricity());
        
        ImGui::Text("Center: %s, Radii: %s", conicSection->Center().c_str(), conicSection->Radii().c_str());

        ImGui::Text(" ");

        ImGui::Text("Parameters: ");
        Updated |= ImGui::InputFloat("x^2", &x2, 0.1f, 1.0f, "%.4f");
        Updated |= ImGui::InputFloat("y^2", &y2, 0.1f, 1.0f, "%.4f");
        Updated |= ImGui::InputFloat("xy",  &xy, 0.1f, 1.0f, "%.4f");
        Updated |= ImGui::InputFloat("x",   &x,  0.1f, 1.0f, "%.4f");
        Updated |= ImGui::InputFloat("y",   &y,  0.1f, 1.0f, "%.4f");
        Updated |= ImGui::InputFloat("c",   &c,  0.1f, 1.0f, "%.4f");
        Updated |= ImGui::InputFloat("scale", &scale, 0.1f, 1.0f, "%.4f");
        Updated |= ImGui::InputFloat("threshold", &threshold, 0.1f, 1.0f, "%.4f");

        ImGui::Text(" ");

        ImGui::Text("Default increment is 0.1, hold 'Ctrl' to increment by 1.");
        ImGui::Text("The origin [0, 0] is in the center of the screen.");
        ImGui::Text("Performance: %.2f ms frametime, %.2f FPS", ImGui::GetIO().DeltaTime * 1000.0f, ImGui::GetIO().Framerate);
        ImGui::Text("The drawing is unfortunately completely serial,\nso the performance suffers with repeated redrawing.");

        ImGui::End();

        if (Updated)
        {
            if (scale < FloatEps) scale = FloatEps;

            Canvas canvas(window.GetWidth(), window.GetHeight(), { 1.0f, 1.0f, 1.0f, 1.0f });
            canvas.SetOffset(window.GetWidth() / 2, window.GetHeight() / 2);

            conicSection->SetParameters(x2, xy, y2, x, y, c);
            conicSection->SetScale(scale);
            conicSection->SetThreshold(threshold);

            canvas.Clear({ 1.0f, 1.0f, 1.0f });
            canvas.Draw(conicSection, { 1.0f, 0.0f, 0.0f, 1.0f });

            tex = Texture(canvas.ImageHandle());

            Updated = false;
        }

        shader.Bind();
        tex.Bind();
        shader.SetUniform1i("uTexture", 0);

        vao.Bind();
        ebo.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        window.EndFrame();
    }

#endif
}