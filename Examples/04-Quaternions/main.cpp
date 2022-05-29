#include "ImguiWindow.h"
#include "Vector.h"
#include "Quaternion.h"
#include "PrintFunctions.h"
#include "Shader.h"
#include "Buffers.h"

#include <vector>
#include <iostream>
#include <string>

using namespace cc;

namespace Cube
{
	struct Vertex
	{
		Vector3 pos;
		Vector2 tex;
	};

	static const std::vector<Vertex> Points =
	{
		{{ -0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f }},
		{{  0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f }},
		{{  0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f }},
		{{ -0.5f,  0.5f, -0.5f }, { 0.0f, 1.0f }},
		
		{{  0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f }},
		{{  0.5f, -0.5f,  0.5f }, { 1.0f, 0.0f }},
		{{  0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f }},
		{{  0.5f,  0.5f, -0.5f }, { 0.0f, 1.0f }},

		{{  0.5f, -0.5f,  0.5f }, { 0.0f, 0.0f }},
		{{ -0.5f, -0.5f,  0.5f }, { 1.0f, 0.0f }},
		{{ -0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f }},
		{{  0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f }},

		{{ -0.5f, -0.5f,  0.5f }, { 0.0f, 0.0f }},
		{{ -0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f }},
		{{ -0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f }},
		{{ -0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f }},

		{{  0.5f, -0.5f,  0.5f }, { 0.0f, 0.0f }},
		{{ -0.5f, -0.5f,  0.5f }, { 1.0f, 0.0f }},
		{{ -0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f }},
		{{  0.5f, -0.5f, -0.5f }, { 0.0f, 1.0f }},

		{{  0.5f,  0.5f,  0.5f }, { 0.0f, 0.0f }},
		{{ -0.5f,  0.5f,  0.5f }, { 1.0f, 0.0f }},
		{{ -0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f }},
		{{  0.5f,  0.5f, -0.5f }, { 0.0f, 1.0f }},
	};

	static const std::vector<uint32_t> Indices =
	{
		 0,  1,  2,
		 0,  2,  3,

		 4,  5,  6,
		 4,  6,  7,

		 8,  9, 10,
		 8, 10, 11,

		12, 13, 14,
		12, 14, 15,

		16, 17, 18,
		16, 18, 19,

		20, 21, 22,
		20, 22, 23,
	};
}

namespace Shaders
{
	static const std::string VertexShader =
	R"(
		#version 330

		location (layout = 0) in vec4 inPos;
		location (layout = 1) in vec2 inTex;

		out vec2 fragTex;

		void main()
		{
			gl_Position = inPos;
		}
	)";

	static const std::string FragmentShader =
	R"(
		#version 330

		in vec2 fragTex;

		uniform sampler2D uTexture;

		out vec4 outColour;

		void main()
		{
			outColout = texture(uTexture, fragTex);
		}
	)";
}

int main()
{
	ImguiWindow window("Quaternions");
	window.SetClearColour({ 0.678f, 0.847f, 0.901f });

	Shader shader(Shaders::VertexShader, Shaders::FragmentShader);

	VertexArray vao;
	VertexBuffer vbo(&Cube::Points[0], Cube::Points.size(), sizeof(Cube::Vertex));
	vbo.GetLayout().AddElement<Float>(3);
	vbo.GetLayout().AddElement<Float>(2);
	vao.AddBuffer(vbo);
	ElementBuffer ebo(&Cube::Indices[0], Cube::Indices.size());

	while (!window.IsClosed())
	{
		window.BeginFrame();

		ImGui::Begin("Options and Info");

		ImGui::Text("Performance: %.2f ms frametime, %.2f FPS", ImGui::GetIO().DeltaTime * 1000.0f, ImGui::GetIO().Framerate);

		ImGui::End();


		shader.Bind();
		vao.Bind();
		ebo.Bind();
		glDrawElements(GL_TRIANGLES, Cube::Indices.size(), GL_UNSIGNED_INT, nullptr);

		window.EndFrame();
	}
}
