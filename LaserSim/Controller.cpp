#include "Controller.h"

#include "Control.h"
#include "Scene.h"
#include "Converter.h"
#include "Object.h"

#include <iostream>


// Constructor
Controller::Controller(Scene* scene, char* window_name) : my_window_name(window_name), my_scene(scene)
{
	my_mat = cv::Mat::zeros(0, 0, CV_8UC3);
}

void Controller::addControl(Control* control)
{

}

// Get the Controller's window name
const char* Controller::windowName() const
{
	return my_window_name;
}

// Get the Scene
Scene* Controller::scene()
{
	return my_scene;
}