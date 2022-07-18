#include <iostream>

#include <RGB.h>
#include <Image.h>
#include <Drawing.h>
#include <ImageUtils.h>
#include <BasicAnimator.h>
#include <Vector.h>
#include <Matrix.h>
#include <Transforms.h>

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

    std::vector<cc::Vector3> centers;
    centers.reserve(cgg_circles.size());
    cc::Vector3 logo_center;
    for (auto [xCenter, yCenter, _] : cgg_circles)
    {
        centers.push_back({ xCenter, yCenter, 0 });
        logo_center.x += xCenter;
        logo_center.y += yCenter;
    }
    logo_center /= cgg_circles.size();

    animator.Animate(
        [&centers, &logo_center] (cc::Image& img, cc::Float t)
        {
            for (size_t i = 0; i < centers.size(); i++)
            {
                cc::Vector3 logo_center_offset = centers[i] - logo_center;
                cc::Matrix4 transform =
                    cc::transform::Translate(
                        cc::transform::RotateY(
                            cc::transform::Translate(
                                cc::transform::Scale(
                                    cc::Matrix4(1), 6
                                ), -logo_center
                            ), 2 * 3.14195 * t 
                        ), { 1280 / 2.0f, 720 / 2.0f, 0 }
                    );
                auto center = transform * logo_center_offset;

                cc::Drawing::DrawCircle(img, center.x, center.y, std::get<2>(cgg_circles[i]) * 6, i < cgg_purple_count ? cgg_purple : cgg_orange);
            }
        }
    );
}
