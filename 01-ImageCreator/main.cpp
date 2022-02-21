#include <iostream>

#include <RGB.h>
#include <Image.h>
#include <Drawing.h>
#include <ImageUtils.h>

#include "cgg_logo.h"

int main(int argc, char ** argv)
{
	cc::Image img(1024, 1024);

    int32_t circleNum = 0;
    for (auto [xCenter, yCenter, radius] : cgg_circles)
    {
        xCenter *= 8;
        yCenter *= 8;
        radius  *= 8;

        if (circleNum < cgg_purple_count)
        {
            cc::Drawing::DrawCircle(img, xCenter, yCenter, radius, cgg_purple);
        }
        else
        {
            cc::Drawing::DrawCircle(img, xCenter, yCenter, radius, cgg_orange);
        }
        ++circleNum;
    }

    cc::ImageUtils::AntiAlias(img);

	cc::Image::Save("img.png", img, cc::ImageType::PNG);

	std::cout << "Generated Image!\n";

    auto loaded = cc::Image::Load("br.jpg");
    if (!loaded)
    {
        std::cout << "Failed to load the image!\n";
    }

    cc::ImageUtils::Greyscale(*loaded);

    cc::Image::Save("br-gr.png", *loaded, cc::ImageType::PNG);
}
