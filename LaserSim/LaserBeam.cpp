#include "LaserBeam.h"

LaserBeam::LaserBeam(std::string name, Location location, Location* intersection, cv::Scalar* color /*= new cv::Scalar(0, 0, 0)*/)
	: Object(BEAM, name, location, Orientation(0, 0, 0), color), my_intersection(intersection)
{
	my_color = new cv::Scalar(0, 0, 255); // TODO: Figure out how to set this default color correctly!
}

Location* LaserBeam::intersection()
{
	return my_intersection;
}