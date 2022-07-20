// The include situation is already very messy, I'll need to do something
// about it soon.
#include "ImguiWindow.h"
#include "Window.h"
#include "RGB.h"
#include "Image.h"
#include "Texture.h"
#include "Shader.h"
#include "Vector.h"
#include "Buffers.h"
#include "Utils.h"

#include "canvas.h"

#include <memory>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>

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

		m_disc = m_xy * m_xy - 4 * m_x2 * m_y2;
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
		if (Equal(m_x2, 0.0f) && Equal(m_y2, 0.0f) && Equal(m_xy, 0.0f))
		{
			return "Linear (or Constant)";
		}

		if (Equal(m_disc, 0.0f))
		{
			return "Parabola";
		}

		if (m_disc > 0)
		{
			return "Hyperbola";
		}
		else
		{
			if (Equal(m_x2, m_y2) && Equal(m_xy, 0.0f))
			{
				if (Equal(m_x2, 0.0f) && Equal(m_y2, 0.0f))
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

	Vector2 Center()
	{
		Vector2 center;

		center.x = (2 * m_y2 * m_x - m_xy * m_y) / m_disc;
		center.y = (2 * m_x2 * m_y - m_xy * m_x) / m_disc;

		return center;
	}

	Vector2 Radii()
	{
		Float num1 = 2 * (m_x2 * m_y * m_y + m_y2 * m_x * m_x - m_xy * m_x * m_y + m_c * m_disc);
		Float num2 = std::sqrt((m_x2 - m_y2) * (m_x2 - m_y2) + m_xy * m_xy);

		Vector2 radii;

		radii.x = -std::sqrt(num1 * ((m_x2 + m_y2) + num2)) / m_disc;
		radii.y = -std::sqrt(num1 * ((m_x2 + m_y2) - num2)) / m_disc;

		return radii;
	}

	Float Angle()
	{
		if (Equal(m_xy, 0.0f))
		{
			if (m_x2 < m_y2)
			{
				return 0.0f;
			}
			else
			{
				return Pi / 2;
			}
		}

		return std::atan((m_y2 - m_x2 - std::sqrt((m_x2 - m_y2) * (m_x2 - m_y2) + m_xy * m_xy)) / m_xy);
	}

	std::string GetConicInfo()
	{
		std::string conicType = DetermineType();
		std::stringstream buffer;

		buffer << "Conic type: " << conicType << ", Eccentricity: " << std::setprecision(4) << Eccentricity() << "\n";
		if (conicType != "Parabola")
		{
			Vector2 center = Center();
			buffer << "Center: [ " << std::setprecision(4) << center.x << ", " << std::setprecision(4) << center.y << " ]\n";
		}
		else
		{
			buffer << "\n";
		}

		if (conicType == "Ellipse")
		{
			Vector2 radii = Radii();

			buffer << "Radii: " << std::setprecision(4) << std::max(radii.x, radii.y) << " on the major axis, and " << std::setprecision(4) << std::min(radii.x, radii.y) << " on the minor axis\n";
			buffer << "Angle: " << std::setprecision(4) << Angle() << " rad (of the major axis from positive x axis)";
		}
		else if (conicType == "Circle")
		{
			Vector2 radii = Radii();

			buffer << "Radius: " << std::setprecision(4) << radii.x << "\n";
		}
		else
		{
			buffer << "\n\n";
		}

		return buffer.str();
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

	Float m_disc;
};

int main()
{
	ImguiWindow window("Conic sections", 640, 480);
	window.SetClearColour({ 1.0f, 0.0f, 0.0f, 1.0f });

	Float x2 = 52, xy = -72, y2 = 73, x = -280, y = 290, c = 325;
	Float min = -1000;
	Float max = 1000;
	Float scale = 128.0f;
	Float threshold = 1;
	int32_t resolution = 1000;
	std::shared_ptr<ConicSection> conicSection = std::make_shared<ConicSection>();
	bool drawImplicit = true;

	Shader shader(vertexShader, fragmentShader);
	Texture tex(Image(640, 480, {1.0f, 1.0f, 1.0f, 1.0f}));

	int32_t idleCounter = 0;
	bool Update = true;

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

		//ImGui::SetWindowFontScale(1.5f);

		ImGui::Text("%s\n", conicSection->GetConicInfo().c_str());

		ImGui::Text(" ");

		ImGui::Text("Parameters: ");
		ImGui::InputFloat("x^2", &x2, 0.1f, 1.0f, "%.4f");
		ImGui::InputFloat("y^2", &y2, 0.1f, 1.0f, "%.4f");
		ImGui::InputFloat("xy",  &xy, 0.1f, 1.0f, "%.4f");
		ImGui::InputFloat("x",   &x,  0.1f, 1.0f, "%.4f");
		ImGui::InputFloat("y",   &y,  0.1f, 1.0f, "%.4f");
		ImGui::InputFloat("c",   &c,  0.1f, 1.0f, "%.4f");
		ImGui::InputFloat("scale", &scale, 0.1f, 1.0f, "%.4f");
		ImGui::InputFloat("threshold", &threshold, 0.1f, 1.0f, "%.4f");
		ImGui::DragInt("ellipse samples", &resolution, 10, 100, 10000);
		ImGui::Checkbox("draw implicitly", &drawImplicit);
		
		ImGui::Text(" ");

		Update = ImGui::Button("Redraw");
		ImGui::Text("Redraws automatically around once per second.");

		ImGui::Text(" ");

		ImGui::Text("Default increment is 0.1, hold 'Ctrl' to increment by 1.");
		ImGui::Text("The origin [0, 0] is in the center of the screen.");
		ImGui::Text("Performance: %.2f ms frametime, %.2f FPS", ImGui::GetIO().DeltaTime * 1000.0f, ImGui::GetIO().Framerate);
		ImGui::Text("The drawing is unfortunately completely serial,\nso the performance suffers with repeated redrawing.");

		ImGui::End();

		threshold = threshold < 0.0f ? 0.0f : threshold;

		if (++idleCounter == 60)
		{
			idleCounter = 0;
			Update = true;
		}

		if (Update)
		{
			if (scale < FloatEps) scale = FloatEps;

			Canvas canvas(window.GetWidth(), window.GetHeight(), { 1.0f, 1.0f, 1.0f, 1.0f });
			canvas.SetOffset(window.GetWidth() / 2, window.GetHeight() / 2);

			conicSection->SetParameters(x2, xy, y2, x, y, c);
			conicSection->SetScale(scale);
			conicSection->SetThreshold(threshold);

			canvas.Clear({ 1.0f, 1.0f, 1.0f });
			if (drawImplicit) canvas.Draw(conicSection, { 1.0f, 0.0f, 0.0f, 1.0f });

			auto conicType = conicSection->DetermineType();
			if (conicType == "Ellipse" || conicType == "Circle")
			{
				Vector2 center = conicSection->Center();
				Vector2 radii = conicSection->Radii();
				Float angle = conicSection->Angle();

				for (int32_t i = 0; i <= resolution; ++i)
				{
					Float t = 2 * Pi * i / resolution;

					Vector2 point;
					point.x = radii.x * std::cos(t) * std::cos(angle) - radii.y * std::sin(t) * std::sin(angle);
					point.y = radii.x * std::cos(t) * std::sin(angle) + radii.y * std::sin(t) * std::cos(angle);

					point += center;
					point *= scale;

					canvas.Draw(point.x, point.y, {0.0f, 1.0f, 0.0f, 1.0f});
				}
			}

			tex = Texture(canvas.ImageHandle());

			Update = false;
		}

		shader.Bind();
		tex.Bind();
		shader.SetUniform1i("uTexture", 0);

		vao.Bind();
		ebo.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		window.EndFrame();
	}
}
