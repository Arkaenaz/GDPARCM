#include "pch.h"
#include "RTImage.h"

RTImage::RTImage(int imageWidth, int imageHeight)
{
	this->imageWidth = imageWidth;
	this->imageHeight = imageHeight;
    this->pixels = std::make_unique<cv::Mat>(cv::Mat::zeros(this->imageHeight, this->imageWidth, CV_8UC3));
}

void RTImage::setPixel(int x, int y, float r, float g, float b, int samplesPerPixel)
{
	float scale = 1.0f / samplesPerPixel;
	r = sqrt(scale * r);
	g = sqrt(scale * g);
	b = sqrt(scale * b);

	int rInt = static_cast<uchar>(256 * std::clamp(r, 0.0f, 0.999f));
	int gInt = static_cast<uchar>(256 * std::clamp(g, 0.0f, 0.999f));
	int bInt = static_cast<uchar>(256 * std::clamp(b, 0.0f, 0.999f));

	cv::Mat imgChannels[3];
	cv::split(*this->pixels, imgChannels);

	imgChannels[0].at<uchar>(this->imageHeight - 1 - y, x) = static_cast<uchar>(bInt);
	imgChannels[1].at<uchar>(this->imageHeight - 1 - y, x) = static_cast<uchar>(gInt);
	imgChannels[2].at<uchar>(this->imageHeight - 1 - y, x) = static_cast<uchar>(rInt);

	cv::merge(imgChannels, 3, *this->pixels);

	// really cool effect lmao
	//cv::Mat src = *this->pixels;
	//cv::flip(src, *this->pixels, 1);
}

void RTImage::saveImage(cv::String& fileName) const
{
	cv::Mat src = *this->pixels;
	cv::flip(src, *this->pixels, 0);
    cv::imwrite(fileName, *this->pixels);
}
