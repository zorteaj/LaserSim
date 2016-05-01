#pragma once

#include "Common.h"

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

class ViewPoint2D;
class Scalar;
class Controller;
class Control;
class Scene;

class Object 
{

public:
	// Constructor
	Object(ObjectType type, std::string name, Location location, Orientation orientation, cv::Scalar* color = new cv::Scalar(0, 0, 0));

	// Destructor
	~Object();

	// Set this Object's location
	void setLocation(Location location);

	// Get this Object's location
	Location location();

	// Set this Object's orienation
	void setOrientation(Orientation orientation);

	//Get this Object's orientation
	Orientation orientation();

	virtual ObjectType type();

	void setColor(cv::Scalar* color);

	cv::Scalar* color();

	Controller* controller();

	void setController(Controller* controller);

	Control* control();

	void setScene(Scene* scene);

	Scene* scene();

	std::string name() const;

protected:

	// Object centers location in meters WRT scene bottom, left, back
	// E.g., a loction of (0, 0, 0) is the bottom -most, left-most, back-most point in the scene
	Location my_location;

	// Objects orientation
	Orientation my_orientation;

	// The type of Object
	ObjectType my_type;

	// The Scene Controller, in which this Object will put its Control
	Controller* my_controller;

	// This Object's Control
	Control* my_control;

	// The Object's color
	cv::Scalar* my_color;

	// The Object's Scene
	Scene* my_scene;

	// This Object's name
	std::string my_name;
};
