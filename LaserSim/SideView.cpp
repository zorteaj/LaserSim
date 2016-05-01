#include "SideView.h"

#include "Scene.h"
#include "Plane.h"
#include "Projector.h"
#include "Converter.h"
#include "LaserBeam.h"
#include "Utils.h"

#include "opencv2/imgproc/imgproc.hpp"

// Constuctor 
SideView::SideView(ViewPointType type, Scene* scene, std::string window_name, int width, int height)
	: ViewPoint2D(type, scene, window_name, width, height)
{

}

// virtual 
// Draws a beam endpoint (laser point) on the target surface, if the beam intersects the target surface
void SideView::projectBeam(ILDAPoint point)
{
	std::cout << "SIDE VIEW: PROJECT BEAM" << std::endl;
}

void SideView::renderPlane(Plane* plane)
{
	cv::Point upper_left;
	upper_left.x = my_converter->coordMetersToPixelsX(my_type, plane->location().meters_y - ((double)plane->depth() / 2));
	upper_left.y = my_converter->coordMetersToPixelsY(my_type, plane->location().meters_z + ((double)plane->height() / 2));

	cv::Point bottom_right;
	bottom_right.x = my_converter->coordMetersToPixelsX(my_type, plane->location().meters_y + ((double)plane->depth() / 2));
	bottom_right.y = my_converter->coordMetersToPixelsY(my_type, plane->location().meters_z - ((double)plane->height() / 2));

	cv::rectangle(my_canvas, upper_left, bottom_right, *(plane->color()) /*,CV_FILLED*/);
}

void SideView::renderProjector(Projector* projector) 
{
	cv::Point location(
		my_converter->coordMetersToPixelsX(my_type, projector->location().meters_y),
		my_converter->coordMetersToPixelsY(my_type, projector->location().meters_z)
		);

	// Set up the pitch arrow
	Location offset(projector->location());

	double offset_distance = 1.0;

	// TODO : I think this causes poor performance.  Optimize memory management
	offset.meters_y = offset.meters_y + cos(rad(projector->orientation().pitch)) * offset_distance;
	offset.meters_z = offset.meters_z + sin(rad(projector->orientation().pitch)) * offset_distance;

	cv::Point end(
		my_converter->coordMetersToPixelsX(my_type, offset.meters_y),
		my_converter->coordMetersToPixelsY(my_type, offset.meters_z)
		);

	cv::circle(my_canvas, location, 25, *(projector->color()), CV_FILLED, 8);
	cv::arrowedLine(my_canvas, location, end, *(projector)->color(), 1, 8, 0, 0.2);
}

void SideView::renderBeam(LaserBeam* beam)
{
	cv::Point start (
		my_converter->coordMetersToPixelsX(my_type, beam->location().meters_y),
		my_converter->coordMetersToPixelsY(my_type, beam->location().meters_z)
		);

	cv::Point end (
		my_converter->coordMetersToPixelsX(my_type, beam->intersection()->meters_y),
		my_converter->coordMetersToPixelsY(my_type, beam->intersection()->meters_z)
		);

	cv::arrowedLine(my_canvas, start, end, *(beam)->color(), 1, 8, 0, 0.000001);
}