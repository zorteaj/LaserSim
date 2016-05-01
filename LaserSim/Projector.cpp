#include "Projector.h"

#include <utility>

#include "Common.h"
#include "Scene.h"
#include "LaserBeam.h"
#include "ParamLine.h"
#include "Scene.h"
#include "Plane.h"
#include "NetOrientation.h"

// Constructor
Projector::Projector(std::string name, Location location, Orientation orientation, double scanner_angle, double radius/* = DEFAULT_PROJECTOR_RADIUS*/, cv::Scalar* color /* = new cv::Scalar(0, 0, 0)*/)
	: Object(PROJECTOR, name, location, orientation, color), my_radius(radius), my_scanner_angle(scanner_angle), my_frame(0)
{
	Scanner_Half_Size = 32768.0;
	my_adj_point_angle = my_scanner_angle / Scanner_Half_Size;
	my_frame = 0;
	my_net_orientation = new NetOrientation(this);
}

// Destructor
Projector::~Projector()
{
	delete my_frame;
	delete my_net_orientation;
}

void Projector::project()
{
	my_laserbeams.clear();

	if (my_frame == nullptr)
	{
		return;
	}

	// For each ILDAPoint
	for (ILDAFrame::iterator point_iter = my_frame->begin(); point_iter < my_frame->end(); point_iter++)
	{
		// The pitch angle in degrees between this ILDAPoint and the projector center
		// Positive values are above the center, negative values are below the center
		double relative_pitch = point_iter->x * my_adj_point_angle;

		// The pitch angle in degrees between level pitch (facing directly forward) and this ILDAPoint
		double absolute_pitch = my_orientation.pitch + relative_pitch;

		// The pitch angle in degrees between this ILDAPoint and the projector center
		// Positive values are above right of the center, negative values are left of the center
		double relative_yaw = point_iter->y * my_adj_point_angle;

		// The pitch angle in degrees between level pitch (facing directly forward) and this ILDAPoint
		double absolute_yaw = my_orientation.yaw + relative_yaw;

		// TODO: We're ignoring roll for now
		ParamLine line = ParamLine(&my_location, new Orientation(absolute_pitch, absolute_yaw, my_orientation.roll));

		// Determine the plane intersection and set it so that when project is called, the intersction can be drawn
		// TODO: This does not account for objects blocking objects that they're in front of
		std::vector<Object*> scene_objs = my_scene->objects();
		for (std::vector<Object*>::iterator obj_iter = scene_objs.begin(); obj_iter < scene_objs.end(); obj_iter++)
		{
			if ((*obj_iter)->type() == PLANE) {
				// TODO: This assumes that the plane is parallel to the x axis for now
				Plane* plane = dynamic_cast<Plane*>(*obj_iter);

				// TODO: Comment what this is doing
				double t = (plane->location().meters_y - (plane->depth()/2) - line.paramY().first) / line.paramY().second;
				Location* intersection = new Location(
					my_scene->resolution(),
					Location::METERS,
					line.paramX().first + line.paramX().second * t,
					line.paramY().first + line.paramY().second * t,
					line.paramZ().first + line.paramZ().second * t
					);
				my_laserbeams.push_back(new LaserBeam("TEST_LASER", this->location(), intersection));
			}
		}
	}

	for (std::vector<LaserBeam*>::iterator iter = my_laserbeams.begin(); iter < my_laserbeams.end(); iter++)
	{
		my_scene->addObject(*iter);
	}
}

// Based on this projector's location, figure out laser beam location on all object's in the scene
// (let's start out with one object, then figure out how to handle mulitple objects)
void Projector::inputILDAFrame(ILDAFrame* frame) {
	this;
	if (my_frame)
	{
		delete my_frame;
	}
	my_frame = frame;
}


// Get Projector's radius
double Projector::radius()
{
	return my_radius;
}

// Set Projector's radius
void Projector::setRadius(double radius)
{
	my_radius = radius;
}

// Set Scene
void Projector::setScene(Scene* scene)
{
	my_scene = scene;
}

const std::vector<LaserBeam*>& Projector::beams()
{
	return my_laserbeams;
}

NetOrientation* Projector::net_orientation()
{
	return my_net_orientation;
}