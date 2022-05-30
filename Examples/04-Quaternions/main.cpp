 #include "ImguiWindow.h"
#include "Vector.h"
#include "Quaternion.h"
#include "PrintFunctions.h"
#include "Shader.h"
#include "Buffers.h"
#include "Image.h"
#include "Texture.h"
#include "ColourUtils.h"
#include "Utils.h"
#include "Transforms.h"

//#define PREP_TEXTURES

#include <vector>
#include <iostream>
#include <string>

#ifdef PREP_TEXTURES
#include <fstream>
#include <iomanip>
#endif

#include "textures.h"

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
		// Sides
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

		// Bottom
		{{  0.5f, -0.5f,  0.5f }, { 0.0f, 0.0f }},
		{{ -0.5f, -0.5f,  0.5f }, { 1.0f, 0.0f }},
		{{ -0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f }},
		{{  0.5f, -0.5f, -0.5f }, { 0.0f, 1.0f }},

		// Top
		{{  0.5f,  0.5f,  0.5f }, { 0.0f, 0.0f }},
		{{ -0.5f,  0.5f,  0.5f }, { 1.0f, 0.0f }},
		{{ -0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f }},
		{{  0.5f,  0.5f, -0.5f }, { 0.0f, 1.0f }},
	};

	static const std::vector<uint32_t> Indices =
	{
		//Sides
		 0,  1,  2,
		 0,  2,  3,

		 4,  5,  6,
		 4,  6,  7,

		 8,  9, 10,
		 8, 10, 11,

		12, 13, 14,
		12, 14, 15,

		// Bottom
		16, 17, 18,
		16, 18, 19,

		// Top
		20, 21, 22,
		20, 22, 23,
	};

	static const std::vector<uint32_t> SideIndices =
	{
		//Sides
		 0,  1,  2,
		 0,  2,  3,

		 4,  5,  6,
		 4,  6,  7,

		 8,  9, 10,
		 8, 10, 11,

		12, 13, 14,
		12, 14, 15,
	};

	static const std::vector<uint32_t> BottomIndices =
	{
		// Bottom
		16, 17, 18,
		16, 18, 19,
	};

	static const std::vector<uint32_t> TopIndices =
	{
		// Top
		20, 21, 22,
		20, 22, 23,
	};
}

namespace Shaders
{
	static const std::string VertexShader =
	R"(
		#version 330

		layout (location = 0) in vec4 inPos;
		layout (location = 1) in vec2 inTex;

		uniform mat4 uModel;
		uniform mat4 uView;
		uniform mat4 uProj;

		out vec2 fragTex;

		void main()
		{
			gl_Position = uProj * uView * uModel * inPos;
			fragTex = inTex;
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
			outColour = texture(uTexture, fragTex);
		}
	)";
}

int main()
{
#ifndef PREP_TEXTURES
	ImguiWindow window("Quaternions");
	window.SetClearColour({ 0.678f, 0.847f, 0.901f });

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	Shader shader(Shaders::VertexShader, Shaders::FragmentShader);

	VertexArray vao;
	VertexBuffer vbo(&Cube::Points[0], Cube::Points.size(), sizeof(Cube::Vertex));
	vbo.GetLayout().AddElement<Float>(3);
	vbo.GetLayout().AddElement<Float>(2);
	vao.AddBuffer(vbo);

	ElementBuffer cubeSideEbo(&Cube::SideIndices[0], Cube::SideIndices.size());
	ElementBuffer cubeTopEbo(&Cube::TopIndices[0], Cube::TopIndices.size());
	ElementBuffer cubeBottomEbo(&Cube::BottomIndices[0], Cube::BottomIndices.size());

	Texture sideGrassTex = Texture(GetGrassSide());
	Texture topGrassTex = Texture(GetGrassTop());
	Texture bottomGrassTex = Texture(GetGrassBottom());

	Quaternion quatStart = Quaternion::Make(Pi/2, { 1.0f, 0.0f, 0.0f });
	Quaternion quatEnd   = Quaternion::Make(-Pi, { 1.0f, 1.0f, 0.0f });
	Float slerpValue = 0.0f;

	while (!window.IsClosed())
	{
		window.BeginFrame();

		ImGui::Begin("Options and Info");

		ImGui::SliderFloat("Interpolation", &slerpValue, 0.0f, 1.0f, "%.4f");

		ImGui::Text("Performance: %.2f ms frametime, %.2f FPS", ImGui::GetIO().DeltaTime * 1000.0f, ImGui::GetIO().Framerate);

		ImGui::End();

		vao.Bind();
		shader.Bind();
		shader.SetUniform1i("uTexture", 0);
		shader.SetUniformMatrix4("uModel", Slerp(slerpValue, quatStart, quatEnd).ToMatrix4());
		shader.SetUniformMatrix4("uView",  Matrix4(1.0f));
		shader.SetUniformMatrix4("uProj", transform::Perspective(16.0f / 9.0f, Pi / 2, 0.1f, 1000.0f));

		sideGrassTex.Bind(0);
		cubeSideEbo.Bind();
		glDrawElements(GL_TRIANGLES, Cube::SideIndices.size(), GL_UNSIGNED_INT, nullptr);

		topGrassTex.Bind(0);
		cubeTopEbo.Bind();
		glDrawElements(GL_TRIANGLES, Cube::TopIndices.size(), GL_UNSIGNED_INT, nullptr);

		bottomGrassTex.Bind(0);
		cubeBottomEbo.Bind();
		glDrawElements(GL_TRIANGLES, Cube::BottomIndices.size(), GL_UNSIGNED_INT, nullptr);

		window.EndFrame();
	}
#else
	// This is irrelevant without the input files,
	// I'm only keeping this temporarily, before I create a better
	// serialization utility.

	auto grassTopOpt = Image::Load("grass_top.png");
	auto grassBottomOpt = Image::Load("dirt.png");
	auto grassSideOpt = Image::Load("grass_side.png");

	if (!grassTopOpt || !grassBottomOpt || !grassSideOpt)
	{
		std::cout << "Failed to load images!\n";
	}

	Image& grassTop = *grassTopOpt;
	Image& grassBottom = *grassBottomOpt;
	Image& grassSide = *grassSideOpt;
		

	for (size_t i = 0; i < 16; i++)
	{
		for (size_t j = 0; j < 16; j++)
		{
			grassTop(i, j) *= RGBA(RGBA8{ 145, 189, 89, 255 });
		}
	}

	std::ofstream plain_grass_top("grass_top_out.txt");
	for (size_t i = 0; i < 16; i++)
	{
		for (size_t j = 0; j < 16; j++)
		{
			RGBA8 temp = RGBA8(grassTop(i, j));
			plain_grass_top << "\tgrassTop(" << std::setw(2) << i << ", " << std::setw(2) << j << ") = RGBA(RGBA8{" << std::setw(3) << (int)temp.r << ", " << std::setw(3) << (int)temp.g << ", " << std::setw(3) << (int)temp.b << ", 255});\n";
		}
	}
	plain_grass_top.close();

	std::ofstream plain_grass_bottom("grass_bottom_out.txt");
	for (size_t i = 0; i < 16; i++)
	{
		for (size_t j = 0; j < 16; j++)
		{
			RGBA8 temp = RGBA8(grassBottom(i, j));
			plain_grass_bottom << "\tgrassBottom(" << std::setw(2) << i << ", " << std::setw(2) << j << ") = RGBA(RGBA8{" << std::setw(3) << (int)temp.r << ", " << std::setw(3) << (int)temp.g << ", " << std::setw(3) << (int)temp.b << ", 255});\n";
		}
	}
	plain_grass_bottom.close();

	std::ofstream plain_grass_side("grass_side_out.txt");
	for (size_t i = 0; i < 16; i++)
	{
		for (size_t j = 0; j < 16; j++)
		{
			RGBA8 temp = RGBA8(grassSide(i, j));
			plain_grass_side << "\tgrassSide(" << std::setw(2) << i << ", " << std::setw(2) << j << ") = RGBA(RGBA8{" << std::setw(3) << (int)temp.r << ", " << std::setw(3) << (int)temp.g << ", " << std::setw(3) << (int)temp.b << ", 255});\n";
		}
	}
	plain_grass_side.close();
#endif
}
