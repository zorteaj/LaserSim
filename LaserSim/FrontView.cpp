#include "FrontView.h"

#include "Scene.h"
#include "Plane.h"
#include "Projector.h"
#include "Converter.h"
#include "LaserBeam.h"

#include "opencv2/imgproc/imgproc.hpp"

FrontView::FrontView(ViewPointType type, Scene* scene, std::string window_name, int width, int height)
	: ViewPoint2D(type, scene, window_name, width, height)
{

}

// virtual 
// Draws a beam endpoint (laser point) on the target surface, if the beam intersects the target surface
void FrontView::projectBeam(ILDAPoint point)
{
	std::cout << "FRONT VIEW: PROJECT BEAM" << std::endl;
}

void FrontView::renderPlane(Plane* plane) {
	cv::Point upper_left;
	upper_left.x = my_converter->coordMetersToPixelsX(my_type, plane->location().meters_x -(double) (plane->width() / 2));
	upper_left.y = my_converter->coordMetersToPixelsY(my_type, plane->location().meters_z + (double) (plane->height() / 2));

	cv::Point bottom_right;
	bottom_right.x = my_converter->coordMetersToPixelsX(my_type, plane->location().meters_x + (double) (plane->width() / 2));
	bottom_right.y = my_converter->coordMetersToPixelsY(my_type, plane->location().meters_z - (double) (plane->height() / 2));

	// TODO: Undo filled for better performance
	cv::rectangle(my_canvas, upper_left, bottom_right, *(plane->color()) /*,CV_FILLED*/);
}

void FrontView::renderProjector(Projector* projector)
{
	cv::Point location(
		my_converter->coordMetersToPixelsX(my_type, projector->location().meters_x),
		my_converter->coordMetersToPixelsY(my_type, projector->location().meters_z)
		);

	cv::circle(my_canvas, location, 25, *(projector->color())/*, CV_FILLED, 8*/);
}

void FrontView::renderBeam(LaserBeam* beam) {
	cv::Point location(
		my_converter->coordMetersToPixelsX(my_type, beam->intersection()->meters_x),
		my_converter->coordMetersToPixelsY(my_type, beam->intersection()->meters_z)
		);

	cv::circle(my_canvas, location, 3, *(beam->color()) /*, CV_FILLED, 8 */);
}