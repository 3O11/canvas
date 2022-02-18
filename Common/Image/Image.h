#ifndef _CC_IMAGE_H
#define _CC_IMAGE_H

#include "../Colour/RGB.h"

#include <cstdint>
#include <vector>
#include <string>
#include <optional>

namespace cc
{
	class Image;
	class Image8;

	enum class ImageType
	{
		PNG,
		JPG,
	};

	class Image final
	{
	public:
		Image(size_t width, size_t height);
		Image(size_t width, size_t height, const RGBA& fillColour);
		Image(const Image8& img8);

		RGBA& operator() (size_t x, size_t y);
		const RGBA& operator() (size_t x, size_t y) const;

		RGBA& operator[] (size_t pixelIndex);
		const RGBA& operator[] (size_t pixelIndex) const;

		size_t Width() const;
		size_t Height() const;
		size_t PixelCount() const;

		static std::optional<Image> Load(std::string_view filepath);
		static void  Save(std::string_view filepath, const Image& image, ImageType type);

	private:
		std::vector<RGBA> m_Pixels;
		size_t m_Width;
		size_t m_Height;
	};

	class Image8 final
	{
	public:
		Image8(size_t width, size_t height);
		Image8(size_t width, size_t height, const RGBA8& fillColour);
		Image8(const Image& img);

		RGBA8& operator() (size_t x, size_t y);
		const RGBA8& operator() (size_t x, size_t y) const;

		RGBA8& operator[] (size_t pixelIndex);
		const RGBA8& operator[] (size_t pixelIndex) const;

		size_t Width() const;
		size_t Height() const;
		size_t PixelCount() const;

		static std::optional<Image8> Load(std::string_view filepath);
		static void                  Save(std::string_view filepath, const Image8& image, ImageType type);

	private:
		std::vector<RGBA8> m_Pixels;
		size_t m_Width;
		size_t m_Height;
	};
}

#endif //_CC_IMAGE_H
