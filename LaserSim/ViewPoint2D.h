#pragma once

#include <iostream>

#include "opencv2/highgui/highgui.hpp"

#include "Common.h"

class Scene;
class Object;
class Converter;
class Plane;
class Projector;
class LaserBeam;

/**
 * ViewPoint Interface
 *
 * Used to represent the scene from a particular perspective
 * Subclasses must implement the projectBeam(...) function
 *
 */
class ViewPoint2D 
{
	
public:

	// Constuctor 
	ViewPoint2D(ViewPointType type, Scene* scene, std::string name, int width, int height);

	// pure virtual
	virtual void addObject(Object* obj);

	// shows viewpoint window in current state
	void show();

	// Abstract function (must be implemented by subclass)
	// Draws a beam endpoint (laser point) on the target surface, if the beam intersects the target surface
	virtual void projectBeam(ILDAPoint point) = 0;

	// Draws the Object to the canvas
	void renderObject(Object* object);

	// Draws the Plane to the canvas, given the perspective of this ViewPoint2D
	virtual void renderPlane(Plane* plane) = 0;

	// Draws the Plane to the canvas, given the perspective of this ViewPoint2D
	virtual void renderProjector(Projector* projector) = 0;

	// Draws the Beam to the canvas, given the perspective of this ViewPoint2D
	virtual void renderBeam(LaserBeam* projector) = 0;

	// Get this ViewPoint's canvas
	cv::Mat canvas();

	// Get this ViewPoint's type
	ViewPointType type();

	// Clear Beams
	void clearBeams();

protected:
	// A refernce to the Scene to which this ViewPoint belongs
	Scene* my_scene;

	// A coordinate converter
	Converter* my_converter;

	// The type of Viewpoint this is
	ViewPointType my_type;

	// A list of the Objects to be displayed in this ViewPoint
	std::vector<Object*> my_objects;

	// Laser beams should be handled differnetly,
	// because they need updating each frame and object location change
	std::vector<LaserBeam*> my_beams;

	// Mat pixels per meter; e.g., resolution of 10 means that 10 Mat pixels represents 1 meter
	int my_resolution;

	// The name of this viewpoint - used for window name
	std::string my_name;

	// That mat that frames this Viewpoint
	cv::Mat my_canvas;

	// The width of this ViewPoint in meters
	int my_width;

	// The height of thie ViewPoint in meters
	int my_height;
};
