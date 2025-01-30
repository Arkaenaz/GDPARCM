#pragma once

#include <opencv2/core.hpp>

class RTImage
{
public:
	explicit RTImage(int imageWidth, int imageHeight);

	void setPixel(int x, int y, float r, float g, float b, int samplesPerPixel = 1);
	void saveImage(cv::String& fileName) const;

private:
	std::unique_ptr<cv::Mat> pixels;
	int imageWidth;
	int imageHeight;
};

