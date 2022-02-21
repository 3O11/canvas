#ifndef _CC_IMAGE_H
#define _CC_IMAGE_H

#include "RGB.h"

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
		Image(int32_t width, int32_t height);
		Image(int32_t width, int32_t height, const RGBA& fillColour);
		Image(const Image8& img8);

		RGBA& operator() (int32_t x, int32_t y);
		const RGBA& operator() (int32_t x, int32_t y) const;

		RGBA& operator[] (int32_t pixelIndex);
		const RGBA& operator[] (int32_t pixelIndex) const;

		int32_t Width() const;
		int32_t Height() const;
		int32_t PixelCount() const;

		static std::optional<Image> Load(std::string_view filepath);
		static void  Save(std::string_view filepath, const Image& image, ImageType type);

	private:
		std::vector<RGBA> m_Pixels;
		int32_t m_Width;
		int32_t m_Height;
	};

	class Image8 final
	{
	public:
		Image8(int32_t width, int32_t height);
		Image8(int32_t width, int32_t height, const RGBA8& fillColour);
		Image8(const Image& img);

		RGBA8& operator() (int32_t x, int32_t y);
		const RGBA8& operator() (int32_t x, int32_t y) const;

		RGBA8& operator[] (int32_t pixelIndex);
		const RGBA8& operator[] (int32_t pixelIndex) const;

		int32_t Width() const;
		int32_t Height() const;
		int32_t PixelCount() const;

		static std::optional<Image8> Load(std::string_view filepath);
		static void                  Save(std::string_view filepath, const Image8& image, ImageType type);

	private:
		std::vector<RGBA8> m_Pixels;
		int32_t m_Width;
		int32_t m_Height;
	};
}

#endif //_CC_IMAGE_H
