#ifndef _CC_DRAWING_H
#define _CC_DRAWING_H

#include "Image.h"

namespace cc
{
	class Drawing
	{
	public:
		static void DrawCircle(Image& img, int32_t xCenter, int32_t yCenter, float radius, const RGB& colour);
	private:
	};
}

#endif //_CC_DRAWING_H
