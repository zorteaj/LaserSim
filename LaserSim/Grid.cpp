#include "Grid.h"

#include "Scene.h"
#include "ViewPoint2D.h"
#include "Converter.h"

// Constructor
Grid::Grid(Scene* scene, int tick_spacing, double tick_length /*= 0.25*/)
	: my_scene(scene), my_tick_spacing(tick_spacing), my_tick_length(tick_length)
{
	my_converter = Converter::Instance();
	my_color = cv::Scalar(255, 255, 255);
}

// Draws the Grid to its ViewPoint2D
void Grid::draw()
{
	for (std::vector<ViewPoint2D*>::const_iterator vp_iter = my_scene->viewPoints().begin(); vp_iter < my_scene->viewPoints().end(); vp_iter++)
	{
		int width; // of Grid in Meters
		int height = my_scene->height(); // of Grid in Meters

		// TOOD: This would need to be reworked to allow other view perspectives
		if ((*vp_iter)->type() == FRONT)
		{
			width = my_scene->width();
		}
		else if ((*vp_iter)->type() == SIDE)
		{
			width = my_scene->depth();
		}

		cv::Mat canvas = (*vp_iter)->canvas();

		// x ticks
		for (int i = 1; i <= width / my_tick_spacing; i++) {
			cv::Point start(my_converter->unitMetersToPixels(my_tick_spacing) * i, canvas.rows);
			cv::Point end(my_converter->unitMetersToPixels(my_tick_spacing) * i, canvas.rows - my_converter->unitMetersToPixels(my_tick_length));
			cv::arrowedLine(canvas, start, end, my_color, 1, 8, 0, 0.000001);
		}

		// y ticks
		for (int i = 1; i <= height / my_tick_spacing; i++) {
			cv::Point start(0, my_converter->unitMetersToPixels(i));
			cv::Point end(my_converter->unitMetersToPixels(my_tick_length), my_converter->unitMetersToPixels(i));
			cv::arrowedLine(canvas, start, end, my_color, 1, 8, 0, 0.000001);
		}
	}
}

// Sets this Grid's tick spacing in meters
void Grid::setTickSpacing(int tick_spacing)
{
	my_tick_spacing = tick_spacing;
}

// Sets this Grid's tick length in meters
void Grid::setTickLength(double tick_length)
{
	my_tick_length = tick_length;
}