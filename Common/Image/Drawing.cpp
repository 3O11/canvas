#include "Drawing.h"

#include <cmath>

namespace cc
{
	void Drawing::DrawCircle(Image& img, int32_t xCenter, int32_t yCenter, float radius, const RGB& colour)
	{
		float r = radius * 1.1f; // to have some kind of safety margin

		int32_t left   = std::max(static_cast<int32_t>(xCenter - r), 0);
		int32_t right  = std::min(static_cast<int32_t>(xCenter + r), static_cast<int32_t>(img.Width()));

		int32_t top    = std::max(static_cast<int32_t>(yCenter - r), 0);
		int32_t bottom = std::min(static_cast<int32_t>(yCenter + r), static_cast<int32_t>(img.Height()));

		for (int32_t row = top; row < bottom; ++row)
		{
			for (int32_t col = left; col < right; ++col)
			{
				float xDist = static_cast<float>(col) - xCenter;
				float yDist = static_cast<float>(row) - yCenter;
				float dist = std::sqrt(xDist * xDist + yDist * yDist);

				if (dist < radius)
				{
					img(col, row) = colour;
				}
			}
		}
	}
}