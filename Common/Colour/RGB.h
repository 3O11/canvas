#ifndef _CC_RGB_H
#define _CC_RGB_H

#include <cstdint>

namespace cc
{
	struct RGB;
	struct RGBA;
	struct RGB8;
	struct RGBA8;

	struct RGB final
	{
		RGB();
		RGB(float bw);
		RGB(float r, float g, float b);
		RGB(const RGB8& rgb);

		float r;
		float g;
		float b;
	};

	struct RGBA final
	{
		RGBA();
		RGBA(float bw);
		RGBA(float r, float g, float b);
		RGBA(float r, float g, float b, float a);
		RGBA(const RGB& rgb);
		RGBA(const RGBA8& rgba);

		float r;
		float g;
		float b;
		float a;
	};

	struct RGB8 final
	{
		RGB8();
		RGB8(uint8_t bw);
		RGB8(uint8_t r, uint8_t g, uint8_t b);
		RGB8(const RGB& rgba);

		uint8_t r;
		uint8_t g;
		uint8_t b;
	};

	struct RGBA8 final
	{
		RGBA8();
		RGBA8(uint8_t bw);
		RGBA8(uint8_t r, uint8_t g, uint8_t b);
		RGBA8(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
		RGBA8(const RGB8& rgb);
		RGBA8(const RGBA& rgba);

		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;
	};
}

#endif //_CC_RGB_H