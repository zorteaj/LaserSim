#pragma once

#include "opencv2/imgproc/imgproc.hpp"

class Scene;
class Converter;

class Grid {

public:
	// Constructor
	Grid(Scene* scene, int tick_spacing, double tick_length = 0.25);

	// Draws the Grid to its ViewPoint2D
	void draw();

	// Sets this Grid's tick spacing in meters
	void setTickSpacing(int tick_spacing);

	// Sets this Grid's tick length in meters
	void setTickLength(double tick_length);

private:
	// The ViewPoint2D on this Grid is drawn
	Scene* my_scene;

	// Space between grid ticks in meters
	int my_tick_spacing;

	// Tick length in meters
	double my_tick_length;

	// The Grid's Converter
	Converter* my_converter;

	// The Grid's line color
	cv::Scalar my_color;
};