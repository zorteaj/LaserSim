#include <iostream>

#include "Scene.h"
#include "Controller.h"
#include "SideView.h"
#include "FrontView.h"
#include "Plane.h"
#include "Projector.h"
#include "Converter.h"
#include "Grid.h"
#include "NetOrientation.h"

#include "opencv2/imgproc/imgproc.hpp"

int frame_rate = 350; // ms

int main() {

	// Define the scene as 20 meter sided cube, with a 50 px/meter resolution
	Scene scene(20, 50);

	// TODO: Test setting grid spacing

	// Create viewpoints for the scene
	scene.addViewPoint(ViewPointType::FRONT);
	scene.addViewPoint(ViewPointType::SIDE);

	// This only works fine because the scene is a cube
	scene.grid()->setTickLength(20);

	Projector* projector = new Projector(
		"Proj",
		Location(scene.resolution(), Location::METERS, 10, 0, 10),
		Orientation(0, 0, 0),
		25
		);

	// Create a 10x10 meter plane centered in the center of the Scene
	Plane* surface = new Plane(
		"Surface",
		//Location(scene.resolution(), Location::METERS, scene.width() / 2, scene.depth() / 2, scene.height() / 2),
		Location(scene.resolution(), Location::METERS, 10, 14, 10),
		Orientation(0, 0, 0),
		18, 16, 8,
		new cv::Scalar(255, 0, 0)
		);

	// Create a second test plane
	Plane* test = new Plane(
		"Test",
		Location(scene.resolution(), Location::METERS, 5, 4, 5),
		Orientation(0, 0, 0),
		8, 2, 1
		);

	// Add Objects to the Scene
	scene.addObject(projector);
	scene.addObject(surface);
	//scene.addObject(test);

	while (true)
	{
		// Define new ILDAFrame
		ILDAFrame* frame = new ILDAFrame();

		// Add ILDAPoints to the frame
		frame->push_back(ILDAPoint(0, 0));

		frame->push_back(ILDAPoint(32767, 32767));
		frame->push_back(ILDAPoint(32767, -32768));
		frame->push_back(ILDAPoint(-32768, -32768));
		frame->push_back(ILDAPoint(-32768, 32767));

		frame->push_back(ILDAPoint(10000, 2000));
		frame->push_back(ILDAPoint(-1000, -3000));
		frame->push_back(ILDAPoint(32000, 2700));
		frame->push_back(ILDAPoint(-3200, 0));
		frame->push_back(ILDAPoint(-10000, 0));
		frame->push_back(ILDAPoint(35000, 1000));
		frame->push_back(ILDAPoint(-1000, 1000));
		frame->push_back(ILDAPoint(3200, 32000));
		frame->push_back(ILDAPoint(-3200, 10000));
		frame->push_back(ILDAPoint(-1000, 30200));

		// Feed the ILDAFrame to the Scene's projector
		scene.projector()->net_orientation()->refresh();
		scene.projector()->inputILDAFrame(frame);
		scene.refresh();

		// keep my window shown indefinitely
		cv::waitKey(frame_rate);
	}
	return 0;
}