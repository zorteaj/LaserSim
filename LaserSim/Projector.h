#pragma once

#include "Object.h"
#include "Common.h"

class LaserBeam;
class Scene;
class NetOrientation;

class Projector : public Object 
{

public:
	// Constructor
	Projector(std::string name, Location location, Orientation orientation, double scanner_angle, double radius = DEFAULT_PROJECTOR_RADIUS, cv::Scalar* color = new cv::Scalar(0, 0, 255));

	// Destructor
	~Projector();

	void project();

	void inputILDAFrame(ILDAFrame* frame);

	// Get Projector's radius
	double radius();

	// Set Projector's radius
	void setRadius(double radius);

	void setScene(Scene* scene);

	const std::vector<LaserBeam*>& beams();

	NetOrientation* net_orientation();

private:
	// The Scene
	Scene* scene;

	// A list of the LaserBeams emitting from this Projector
	std::vector<LaserBeam*> my_laserbeams;

	// The most recent ILDA Frame
	ILDAFrame* my_frame;

	NetOrientation* my_net_orientation;

	// The Projector's radius
	double my_radius;

	// Max angle from center that Beams can emit from Projector center
	double my_scanner_angle;

	// Half the number of ILDAPoints 
	double Scanner_Half_Size;

	// Angle between adjacent ILDA Points
	double my_adj_point_angle;
};