#include "pch.h"
#include "RayTracingThread.h"

#include "camera.h"
#include "RTImage.h"

RayTracingThread::RayTracingThread(int id, 
								   camera* cam, 
								   RTImage* image, 
								   int lowerXBound,
								   int lowerYBound,
								   int upperXBound,
								   int upperYBound,
								   const hittable& world)
	: world(world)
{
    this->running = false;
	this->id = id;
    this->cam = cam;
    this->image = image;
    this->lowerXBound = lowerXBound;
    this->lowerYBound = lowerYBound;
    this->upperXBound = upperXBound;
    this->upperYBound = upperYBound;
}

void RayTracingThread::run()
{
    this->running = true;

    //std::string fileName = "image.png";

    for (int j = lowerYBound; j < upperYBound; j++)
    {
        for (int i = lowerXBound; i < upperXBound; i++) {
        	color pixel_color(0, 0, 0);
            for (int sample = 0; sample < cam->samples_per_pixel; sample++) {
                ray r = cam->get_ray(i, j);
                pixel_color += cam->ray_color(r, cam->max_depth, world);
            }

            const float r = static_cast<float>(pixel_color.x());
            const float g = static_cast<float>(pixel_color.y());
            const float b = static_cast<float>(pixel_color.z());

            this->image->setPixel(i, j, r, g, b, cam->samples_per_pixel);
            pixelsRendered++;
        }
    }

    this->dismiss();
}

void RayTracingThread::dismiss()
{
    //std::cout << "Dismissing Thread #" << this->id << std::endl;
	this->running = false;
}

bool RayTracingThread::isRunning()
{
    return this->running;
}

int RayTracingThread::getPixelsRendered()
{
    return this->pixelsRendered;
}