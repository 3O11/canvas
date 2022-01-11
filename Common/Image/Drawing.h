#ifndef _CC_DRAWING_H
#define _CC_DRAWING_H

#include "Types.h"
#include "Image.h"

namespace cc
{
	class Drawing
	{
	public:
		static void DrawCircle(Image& img, int32_t xCenter, int32_t yCenter, Float radius, const RGB& colour);
	private:
	};
}

#endif //_CC_DRAWING_H
