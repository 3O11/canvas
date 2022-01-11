#include "ImageUtils.h"

#include "../Colour/ColourUtils.h"

namespace cc
{
	void ImageUtils::AntiAlias(Image& img)
	{
		Image result(img.Width(), img.Height());
		int32_t aaRadius = 1;

		for (int32_t row = 0; row < img.Height(); ++row)
		{
			for (int32_t col = 0; col < img.Height(); ++col)
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

				result(col, row) = sum / static_cast<float>(sumCount);
				result(col, row).a = img(col, row).a;
			}
		}

		img = result;
	}
}
