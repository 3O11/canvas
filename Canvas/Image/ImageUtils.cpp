#include "ImageUtils.h"

#include "ColourUtils.h"
#include <cmath>

namespace cc
{
	void ImageUtils::AntiAlias(Image& img)
	{
		Image result(img.Width(), img.Height());
		int32_t aaRadius = 2;

		for (int32_t row = 0; row < img.Height(); ++row)
		{
			for (int32_t col = 0; col < img.Width(); ++col)
			{
				RGBA sum;
				size_t sumCount = 0;

				for (int32_t row_offset = -aaRadius; row_offset <= aaRadius; ++row_offset)
				{
					for (int32_t col_offset = -aaRadius; col_offset <= aaRadius; ++col_offset)
					{
						if (row + row_offset < 0 || row + row_offset >= img.Height() || col + col_offset < 0 || col + col_offset >= img.Width()) continue;

						sum += img(col + col_offset, row + row_offset);
						++sumCount;
					}
				}

				result(col, row) = sum / static_cast<Float>(sumCount);
				result(col, row).a = img(col, row).a;
			}
		}

		img = result;
	}

	void ImageUtils::Greyscale(Image& img)
	{
		for (int32_t row = 0; row < img.Height(); ++row)
		{
			for (int32_t col = 0; col < img.Width(); ++col)
			{
				RGBA& cp = img(col, row);

				cp.r = (cp.r < 0.04045f) ? (cp.r / 12.92f) : ((Float)std::pow(((cp.r + 0.055f) / 1.055f), 2.4f));
				cp.g = (cp.g < 0.04045f) ? (cp.g / 12.92f) : ((Float)std::pow(((cp.g + 0.055f) / 1.055f), 2.4f));
				cp.b = (cp.b < 0.04045f) ? (cp.b / 12.92f) : ((Float)std::pow(((cp.b + 0.055f) / 1.055f), 2.4f));

				float tempGrayscale = (0.2126f * cp.r) + (0.7152f * cp.g) + (0.0722f * cp.b);
				tempGrayscale = (tempGrayscale < 0.0031308f) ? (tempGrayscale * 12.92f) : (((Float)std::pow(tempGrayscale, (1 / 2.4f))) - 0.055f);
				cp.r = cp.g = cp.b = tempGrayscale;
			}
		}
	}
}
