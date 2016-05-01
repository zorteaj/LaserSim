#include "Plane.h"

//Constructor
Plane::Plane(std::string name, Location location, Orientation orientation, int width, int height, int depth, cv::Scalar* color /* = new cv::Scalar(0, 0, 0)*/)
	: Object(PLANE, name, location, orientation, color), my_width(width), my_height(height), my_depth(depth)
{

}

// Get this Plane's width
int Plane::width()
{
	return my_width;
}

// Get this Plane's height
int Plane::height()
{
	return my_height;
}

int Plane::depth()
{
	return my_depth;
}

// TODO: Magnification for depth perspective??

