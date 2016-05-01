#pragma once

#include <vector>

// PI
static const double PI = 3.14159265;


// Default grid tick spacing in meters
static const int DEFAULT_GRID_TICK_SPACING = 1;


// Default raidus of Projector
static const int DEFAULT_PROJECTOR_RADIUS = 2;


// Identifies the types of ViewPoints
enum ViewPointType { FRONT, SIDE };


// Identifies the types of Objects
enum ObjectType {PLANE, PROJECTOR, BEAM};


/**
 * A 2D point in ILDA format
 *
 * Represents a coordinate on the laser scanner
 * Directions in comments are with respect to target surface
 *
 */
struct ILDAPoint
{
	// Constructor
	ILDAPoint(short x, short y)
	{
		this->x = x;
		this->y = y;
	}

	// left/right (extreme left = -32,768; extreme right = 32,767)
	short x;

	// down/up (extreme down = -32,768; extreme up = 32,767)
	short y;
};



// A set of ILDAPoints
typedef std::vector<ILDAPoint> ILDAFrame;



/**
 * 3D cartesian coordinates, in METERS, in the scene
 *
 * Origin (0,0,0) is extreme left, extreme backwards, extreme downwards with respect to target surface
 * Directions in comments are from the point of view  of the projector when facing directly at the target surface
 *
 */
struct Location
{
	enum Unit { MAT, METERS };

	Location(int resolution, Unit unit, double x, double y, double z)
	{
		this->resolution = resolution;
		this->unit = unit;

		if (unit == MAT)
		{
		/*	mat_x = x;
			mat_y = y;
			mat_z = z;*/

			meters_x = x / resolution;
			meters_y = y / resolution;
			meters_y = z / resolution;
		}
		else if (unit == METERS) {
			meters_x = x;
			meters_y = y;
			meters_z = z;

			//mat_x = x * resolution;
			//mat_y = y * resolution;
			//mat_z = z * resolution;
		}
	}


	Location operator +(Location& location)
	{
		return Location(
			this->resolution, 
			this->unit, 
			this->meters_x + location.meters_x,
			this->meters_y + location.meters_y,
			this->meters_z + location.meters_z);
	}

	// TODO: This depends on ViewPointType !! Rename to x, y, z

	//// left/right in Mat pixels (extreme left = 0; extreme right = scene width)
	//double mat_x;

	//// backward/forward in Mat pixels (extreme back = 0; extreme forward = scene depth)
	//double mat_y;

	//// down/up in Mat pixels (extreme down = 0; extreme up = scene height)
	//double mat_z;

	// left/right in meters (extreme left = 0; extreme right = scene width)
	double meters_x;

	// backward/forward in meters (extreme back = 0; extreme forward = scene depth)
	double meters_y;

	// down/up in meters (extreme down = 0; extreme up = scene height)
	double meters_z;

	int resolution;

	Unit unit;
};



/**
 * Orientation as Tait-Bryan angles in DEGREES (pitch, yaw, roll)
 */
struct Orientation
{
	// Constructor
	Orientation(double pitch, double yaw, double roll) {
		this->pitch = pitch;
		this->yaw = yaw;
		this->roll = roll;
	}

	// tilt (up/down) rotation in degrees; 0 degrees is parallel to x-axis, 90 degrees is staright up, -90 degrees is straight down
	double pitch;

	// side (left/right) rotation in degrees; 0 degrees perpendicular to y-axis, 90 degrees if extreme right, -90 degrees is extreme left
	double yaw;

	// bank(around) rotation in degrees; (extreme down = 0; extreme up = scene height)
	double roll;
};