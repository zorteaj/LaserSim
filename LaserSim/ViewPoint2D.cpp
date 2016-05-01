#include "ViewPoint2D.h"

#include "Object.h"
#include "Scene.h"
#include "Converter.h"
#include "Plane.h"
#include "Projector.h"
#include "LaserBeam.h"

// Constuctor 
ViewPoint2D::ViewPoint2D(ViewPointType type, Scene* scene, std::string name, int width, int height)
	: my_type(type), my_scene(scene), my_name(name), my_width(width), my_height(height)
{
	my_converter = Converter::Instance();
	my_canvas = cv::Mat(my_converter->unitMetersToPixels(my_width), my_converter->unitMetersToPixels(my_height), CV_8UC3);
}

void ViewPoint2D::addObject(Object* obj) {
	if (obj->type() == BEAM)
	{
		my_beams.push_back(dynamic_cast<LaserBeam*>(obj));
	}
	else
	{
		my_objects.push_back(obj);
	}
}

void ViewPoint2D::renderObject(Object* object) {
	switch(object->type()) {
	case PLANE: renderPlane(dynamic_cast<Plane*>(object));
		break;
	case PROJECTOR: renderProjector(dynamic_cast<Projector*>(object));
		break;
	case BEAM: renderBeam(dynamic_cast<LaserBeam*>(object));
	}
}

// shows viewpoint window in current state
void ViewPoint2D::show()
{
	for (std::vector<Object*>::iterator iter = my_objects.begin(); iter < my_objects.end(); iter++)
	{
		renderObject(*iter);
	}

	for (std::vector<LaserBeam*>::iterator iter = my_beams.begin(); iter < my_beams.end(); iter++)
	{
		renderObject(*iter);
	}

	cv::imshow(my_name.c_str(), my_canvas);
}

// Get this ViewPoint's canvas
cv::Mat ViewPoint2D::canvas() {
	return my_canvas;
}

// Get this ViewPoint's type
ViewPointType ViewPoint2D::type()
{
	return my_type;
}

void ViewPoint2D::clearBeams()
{
	my_beams.clear();
}