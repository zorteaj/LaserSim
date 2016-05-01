#include "Scene.h"

#include "ViewPointFactory.h"
#include "Projector.h"
#include "Object.h"
#include "ViewPoint2D.h"
#include "Grid.h"
#include "Converter.h"
#include "Controller.h"
#include "LaserBeam.h"

Scene::Scene(int width, int depth, int height, int resolution)
	: my_width(width), my_depth(depth), my_height(height), my_resolution(resolution)
{
	my_converter = Converter::Create(this);
	my_grid = new Grid(this, DEFAULT_GRID_TICK_SPACING);
	my_color = cv::Scalar(250, 206, 135);
	my_controller = new Controller(this, "CONTROLLER");
}

// Constructor
// For cubic scenes (scenes with equal width, depth, and height)
Scene::Scene(int side_length, int resolution)
	: Scene(side_length, side_length, side_length, resolution)
{
	
}

// Destructor
// clean up Viewpoints, Objects, Projector, Grid, and Controller
Scene::~Scene() {
	for (std::vector<ViewPoint2D*>::iterator iter = my_viewpoints.begin(); iter < my_viewpoints.end(); iter++)
	{
		delete *iter;
	}
	for (std::vector<Object*>::iterator iter = my_objects.begin(); iter < my_objects.end(); iter++)
	{
		delete *iter;
	}
	delete my_projector;
	delete my_grid;
	delete my_controller;
}

// Add a viewpoint for this Scene
void Scene::addViewPoint(ViewPointType type)
{
	ViewPoint2D* viewpoint = ViewPointFactory::create(type, this, my_resolution, my_width, my_depth, my_height);
	my_viewpoints.push_back(viewpoint);
}

// Get this Scene's ViewPoint2Ds
const std::vector<ViewPoint2D*>& Scene::viewPoints()
{
	return my_viewpoints;
}

// Adds Object to the Scene by putting the object in Scene's ViewPoint2Ds
// Also gives Object a refernce to this Scene's Controller, in which it wil add its Control
// Also sets Object's Scene to this 
void Scene::addObject(Object* obj) {
	obj->setScene(this);
	if (obj->type() == BEAM)
	{
		my_beams.push_back(dynamic_cast<LaserBeam*>(obj));
	}
	else {
		if (obj->type() == PROJECTOR)
		{
			my_projector = dynamic_cast<Projector*>(obj);
			my_projector->setScene(this); // TODO: Seems this is redundant with the first line of code in this function
		}
		obj->setController(my_controller);
		my_objects.push_back(obj);
	}
	
	for (std::vector<ViewPoint2D*>::iterator iter = my_viewpoints.begin(); iter < my_viewpoints.end(); iter++)
	{
		(*iter)->addObject(obj);
	}
}

// Update this Scene and show the new state
void Scene::refresh()
{
	clear();
	my_projector->project();
	my_grid->draw();
	show();
}

void Scene::clear()
{
	my_beams.clear();
	for (std::vector<ViewPoint2D*>::iterator iter = my_viewpoints.begin(); iter < my_viewpoints.end(); iter++)
	{
		(*iter)->canvas() = my_color;
		(*iter)->clearBeams();
	}
}

void Scene::show()
{
	for (std::vector<ViewPoint2D*>::iterator iter = my_viewpoints.begin(); iter < my_viewpoints.end(); iter++)
	{
		(*iter)->show();
	}
}

// Get this Scene's resolution
int Scene::resolution()
{
	return my_resolution;
}

// Get this Scene's width
int Scene::width() {
	return my_width;
}

// Get this Scene's depth
int Scene::depth() {
	return my_depth;
}

// Get this Scene's height
int Scene::height() {
	return my_height;
}

// Return this scene's projector
Projector* Scene::projector() {
	return my_projector;
}

Grid* Scene::grid() {
	return my_grid;
}

const std::vector<Object*>& Scene::objects()
{
	return my_objects;
}