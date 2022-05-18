#ifndef _CC_COLOUR_UTILS_H
#define _CC_COLOUR_UTILS_H

#include "RGB.h"

namespace cc
{
	RGB  operator+  (const RGB& a, const RGB& b);
	RGB& operator+= (RGB& a, const RGB& b);

	RGBA& operator+= (RGBA& a, const RGBA& b);
	RGBA  operator/  (const RGBA& a, Float s);
	RGBA  operator*  (const RGBA& a, Float s);
}

#endif //_CC_COLOUR_UTILS_H
