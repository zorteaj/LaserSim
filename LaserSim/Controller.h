#pragma once

#include "opencv2/highgui/highgui.hpp"

class Scene;
class Control;

class Controller {

public:
	// Constructor
	Controller(Scene* scene, char* name);

	void addControl(Control* control);

	// Get the Controller's window name
	const char* windowName() const;

	// Get the Scene
	Scene* scene();

private:
	Scene* my_scene;
	const char* my_window_name;
	cv::Mat my_mat;
};