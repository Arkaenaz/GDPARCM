#pragma once

#include "hittable.h"
#include "IETThread.h"

class camera;
class RTImage;
class RayTracingThread final : public IETThread
{
public:
	//RayTracingThread() = default;
	RayTracingThread(int id, camera* cam, RTImage* image, int lowerXBound, int lowerYBound, int upperXBound, int upperYBound, const hittable& world);
	//~RayTracingThread() override;

	void dismiss();
	bool isRunning();
	int getPixelsRendered();

protected:
	void run() override;

private:
	int id;

	bool running;

	camera* cam;
	RTImage* image;
	const hittable& world;
	
	int lowerXBound;
	int lowerYBound;
	int upperXBound;
	int upperYBound;

	int pixelsRendered;
};

