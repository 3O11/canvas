#include "ColourUtils.h"

namespace cc
{
	RGB operator+ (const RGB& a, const RGB& b)
	{
		return { a.r + b.r, a.g + b.g, a.b + b.b };
	}

	RGB& operator+= (RGB& a, const RGB& b)
	{
		a.r += b.r;
		a.g += b.g;
		a.b += b.b;
		return a;
	}

	RGBA& operator+= (RGBA& a, const RGBA& b)
	{
		a.r += b.r;
		a.g += b.g;
		a.b += b.b;
		a.a += b.a;
		return a;
	}

	RGBA operator/(const RGBA& a, Float s)
	{
		return {a.r / s, a.g / s, a.b / s, a.a / s};
	}
}