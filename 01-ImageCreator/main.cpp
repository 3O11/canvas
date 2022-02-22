#include <iostream>

#include <RGB.h>
#include <Image.h>
#include <Drawing.h>
#include <ImageUtils.h>
#include <BasicAnimator.h>

#include "cgg_logo.h"

int main(int argc, char ** argv)
{
    // Test Image generation

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

    // Test BW conversion

    auto loaded = cc::Image::Load("DarkAlley.jpeg");
    if (!loaded)
    {
        std::cout << "Failed to load the image!\n";
        return -1;
    }

    cc::ImageUtils::Greyscale(*loaded);

    cc::Image::Save("DarkAlley-gr.png", *loaded, cc::ImageType::PNG);

    std::cout << "Converted image to Greyscale!\n";

    // Test Animator

    cc::BasicAnimator animator;

    animator.Animate([](cc::Image& img, cc::Float t){ cc::Drawing::DrawCircle(img, t * 1000, t * 700, 10, {1.0f, 0.0f, 0.0f}); });
}
