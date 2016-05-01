#include "Object.h"

#include "ViewPoint2D.h"
#include "Controller.h"
#include "Control.h"
#include "Scene.h"

// Constructor
Object::Object(ObjectType type, std::string name, Location location, Orientation orientation, cv::Scalar* color /* = new cv::Scalar(0, 0, 0)*/ )
	: my_type(type), my_name(name), my_location(location), my_orientation(orientation), my_color(color)
{

}

// Destructor
Object::~Object()
{
	delete my_color;
}

// Set this Object's location
void Object::setLocation(Location location)
{
	my_location = location;
}

// Get this Object's location
Location Object::location()
{
	return my_location;
}

// Set this Object's orienation
void Object::setOrientation(Orientation orientation)
{
	my_orientation = orientation;
}

//Get this Object's orientation
Orientation Object::orientation()
{
	return my_orientation;
}

// Get this Object's type
ObjectType Object::type() {
	return my_type;
}

// Set this Object's color
void Object::setColor(cv::Scalar* color)
{
	my_color = color;
}

// Get this Object's color
cv::Scalar* Object::color()
{
	return my_color;
}

// Set the Controller
void Object::setController(Controller* controller)
{
	my_controller = controller;
	my_control = new Control(this);
}

// Get the Controller
Controller* Object::controller()
{
	return my_controller;
}

// Set the Object's Scene
void Object::setScene(Scene* scene)
{
	my_scene = scene;
}

// Get the Scene that this Object is in
Scene* Object::scene()
{
	return my_scene;
}

std::string Object::name() const
{
	return my_name;
}

Control* Object::control()
{
	return my_control;
}