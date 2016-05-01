#pragma once

#include "Common.h"

#include "opencv2/imgproc/imgproc.hpp"

class ViewPoint2D;
class Projector;
class Object;
class Grid;
class Converter;
class Controller;
class LaserBeam;

class Scene {

public:
	// Constructor 
	Scene(int width, int depth, int height, int resolution);

	// Constructor
	// For cubic scenes (scenes with equal width, depth, and height)
	Scene(int side_length, int resolution);

	// Destructor
	// clean up Viewpoints, Objects, and Projector
	~Scene();

	// Add a viewpoint for this Scene
	void addViewPoint(ViewPointType type);

	// Get this Scene's ViewPoint2Ds
	const std::vector<ViewPoint2D*>& viewPoints();

	// Adds object to the scene
	void addObject(Object* obj);

	// Update this Scene and show the new state
	void refresh();

	// Clear the Scene 
	void clear();

	// Show the Scene
	void show();

	// Get this Scene's resolution
	int resolution();

	// Get this Scene's width in meters
	int width();

	// Get this Scene's depth in meters
	int depth();

	// Get this Scene's height in meters
	int height();

	// Return this Scene's Projector
	Projector* projector();

	// Return this Scene's Grid
	Grid* grid();

	// Return this Scene's Objects
	const std::vector<Object*>& objects();

private:
	// A list of the Viewpoints for this Scene
	std::vector<ViewPoint2D*> my_viewpoints;

	// A list of the Objects in this Scene
	std::vector<Object*> my_objects;

	// Laser beams should be handled differnetly,
	// because they need updating each frame and object location change
	std::vector<LaserBeam*> my_beams;

	// A Converter
	Converter* my_converter;

	// The Controller for this Scene
	Controller* my_controller;

	// The Grid for this Scene
	Grid* my_grid;

	// The projector in this Scene
	Projector* my_projector;

	// Width (left/right) of the Scene in meters
	int my_width;

	// Depth of the Scene (forward/backward) in meters
	int my_depth;

	// Height of the Scene (up/down) in meters
	int my_height;

	// Mat pixels per meter; e.g., resolution of 10 means that 10 Mat pixels represents 1 meter
	int my_resolution;

	// Background color of Scene
	cv::Scalar my_color;
};