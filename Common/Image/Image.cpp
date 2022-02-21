#include "Image.h"

#include "stb_image.h"
#include "stb_image_write.h"

#include <iostream>

namespace cc
{
	// Image

	Image::Image(int32_t width, int32_t height)
		: m_Pixels(width * height, {0.0f, 0.0f, 0.0f, 1.0f}), m_Width(width), m_Height(height)
	{}

	Image::Image(int32_t width, int32_t height, const RGBA& fillColour)
		: m_Pixels(width * height, fillColour), m_Width(width), m_Height(height)
	{}

	Image::Image(const Image8& img8)
		: m_Pixels(img8.Width() * img8.Height()), m_Width(img8.Width()), m_Height(img8.Height())
	{
		for (int32_t i = 0; i < img8.PixelCount(); i++) m_Pixels[i] = img8[i];
	}

	RGBA& Image::operator() (int32_t x, int32_t y)
	{
		return m_Pixels[ (y * m_Height) + x ];
	}

	const RGBA& Image::operator() (int32_t x, int32_t y) const
	{
		return m_Pixels[(y * m_Height) + x];
	}

	RGBA& Image::operator[] (int32_t pixelIndex)
	{
		return m_Pixels[pixelIndex];
	}

	const RGBA& Image::operator[] (int32_t pixelIndex) const
	{
		return m_Pixels[pixelIndex];
	}

	int32_t Image::Width() const
	{
		return m_Width;
	}

	int32_t Image::Height() const
	{
		return m_Height;
	}

	int32_t Image::PixelCount() const
	{
		return m_Width * m_Height;
	}

	std::optional<Image> Image::Load(std::string_view filepath)
	{
		return Image8::Load(filepath);
	}

	void Image::Save(std::string_view filepath, const Image& image, ImageType type)
	{
		Image8::Save(filepath, image, type);
	}

	// Image8

	Image8::Image8(int32_t width, int32_t height)
		: m_Pixels(width* height, { 0, 0, 0, 255 }), m_Width(width), m_Height(height)
	{}

	Image8::Image8(int32_t width, int32_t height, const RGBA8& fillColour)
		: m_Pixels(width* height, fillColour), m_Width(width), m_Height(height)
	{}

	Image8::Image8(const Image& img)
		: m_Pixels(img.Width()* img.Height()), m_Width(img.Width()), m_Height(img.Height())
	{
		for (int32_t i = 0; i < img.PixelCount(); i++) m_Pixels[i] = img[i];
	}

	RGBA8& Image8::operator() (int32_t x, int32_t y)
	{
		return m_Pixels[(y * m_Height) + x];
	}

	const RGBA8& Image8::operator() (int32_t x, int32_t y) const
	{
		return m_Pixels[(y * m_Height) + x];
	}

	RGBA8& Image8::operator[] (int32_t pixelIndex)
	{
		return m_Pixels[pixelIndex];
	}

	const RGBA8& Image8::operator[] (int32_t pixelIndex) const
	{
		return m_Pixels[pixelIndex];
	}

	int32_t Image8::Width() const
	{
		return m_Width;
	}

	int32_t Image8::Height() const
	{
		return m_Height;
	}

	int32_t Image8::PixelCount() const
	{
		return m_Width * m_Height;
	}

	std::optional<Image8> Image8::Load(std::string_view filepath)
	{
		int width, height, channels;
		uint8_t* raw_img = stbi_load(filepath.data(), &width, &height, &channels, 4);

		if (raw_img == nullptr)
		{
			return std::nullopt;
		}

		Image8 img(width, height);
		for (int32_t i = 0; i < static_cast<int32_t>(width) * height; ++i)
		{
			int32_t pxPos = i * 4;
			img[i] = { raw_img[pxPos], raw_img[pxPos + 1], raw_img[pxPos + 2], raw_img[pxPos + 3] };
		}

		stbi_image_free(raw_img);

		return img;
	}

	void Image8::Save(std::string_view filepath, const Image8& image, ImageType type)
	{
		int width = static_cast<int>(image.Width());
		int height = static_cast<int>(image.Height());

		switch (type)
		{
		case ImageType::JPG:
			stbi_write_jpg(filepath.data(), width, height, 4, &image.m_Pixels[0], 100);
			break;
		case ImageType::PNG:
			stbi_write_png(filepath.data(), width, height, 4, &image.m_Pixels[0], width * 4);
			break;
		}
	}
}
