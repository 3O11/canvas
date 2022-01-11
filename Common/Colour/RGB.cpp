#include "RGB.h"

namespace cc
{
	// RGB

	RGB::RGB()
		: r(0.0f), g(0.0f), b(0.0f)
	{}

	RGB::RGB(float bw)
		: r(bw), g(bw), b(bw)
	{}

	RGB::RGB(float r, float g, float b)
		: r(r), g(g), b(b)
	{}

	RGB::RGB(const RGB8& rgb)
		: r(rgb.r / 255.0f), g(rgb.g / 255.0f), b(rgb.b / 255.0f)
	{}

	// RGBA

	RGBA::RGBA()
		: r(0.0f), g(0.0f), b(0.0f), a(1.0f)
	{}

	RGBA::RGBA(float bw)
		: r(bw), g(bw), b(bw), a(1.0f)
	{}

	RGBA::RGBA(float r, float g, float b)
		: r(r), g(g), b(b), a(1.0f)
	{}

	RGBA::RGBA(float r, float g, float b, float a)
		: r(r), g(g), b(b), a(a)
	{}

	RGBA::RGBA(const RGB& rgb)
		: r(rgb.r), g(rgb.g), b(rgb.b), a(1.0f)
	{}

	RGBA::RGBA(const RGBA8& rgba)
		: r(rgba.r / 255.0f), g(rgba.g / 255.0f), b(rgba.b / 255.0f), a(rgba.a / 255.0f)
	{}

	// RGB8

	RGB8::RGB8()
		: r(0), g(0), b(0)
	{}

	RGB8::RGB8(uint8_t bw)
		: r(bw), g(bw), b(bw)
	{}

	RGB8::RGB8(uint8_t r, uint8_t g, uint8_t b)
		: r(r), g(g), b(b)
	{}

	RGB8::RGB8(const RGB& rgb)
		: r(static_cast<uint8_t>(rgb.r * 255)), g(static_cast<uint8_t>(rgb.g * 255)), b(static_cast<uint8_t>(rgb.b * 255))
	{}

	// RGBA8

	RGBA8::RGBA8()
		: r(0), g(0), b(0), a(255)
	{}

	RGBA8::RGBA8(uint8_t bw)
		: r(bw), g(bw), b(bw), a(255)
	{}

	RGBA8::RGBA8(uint8_t r, uint8_t g, uint8_t b)
		: r(r), g(g), b(b), a(255)
	{}

	RGBA8::RGBA8(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
		: r(r), g(g), b(b), a(a)
	{}

	RGBA8::RGBA8(const RGBA& rgba)
		: r(static_cast<uint8_t>(rgba.r * 255)), g(static_cast<uint8_t>(rgba.g * 255)), b(static_cast<uint8_t>(rgba.b * 255)), a(static_cast<uint8_t>(rgba.a * 255))
	{}
}