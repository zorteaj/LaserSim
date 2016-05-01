#pragma once

#include "Object.h"

class LaserBeam : public Object
{
public:
	// Constructor
	LaserBeam(std::string name, Location location, Location* intersection, cv::Scalar* color = new cv::Scalar(0, 0, 0));

	Location* intersection();

private:
	Location* my_intersection;
};