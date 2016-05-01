#pragma once

#include "Object.h"

#include "opencv2/imgproc/imgproc.hpp"

class Plane : public Object 
{

public:
	//Constructor
	Plane(std::string name, Location location, Orientation orientation, int width, int height, int depth, cv::Scalar* color = new cv::Scalar(0, 0, 0));

	// Get this Plane's width
	int width();

	// Get this Plane's height
	int height();

	// Get this Plane's depth
	int depth();

private:

	// width of this Plane in meters
	int my_width;

	// height of this Plane in meters
	int my_height;

	// depth of this Plane in meters
	int my_depth;
};