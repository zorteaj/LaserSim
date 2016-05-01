#include "ParamLine.h"
#include "Utils.h"

// TODO : Test
#include "quaternion.h"

#include <iostream>

ParamLine::ParamLine(Location* origin, Orientation* orientation) : my_origin(origin)
{
	// Define offset_point as origin, to be maniuplated by following function calls
	// TODO: I'm hoping this is a copy constructor, and that I'm not going to accidentally maniuplate the origin
	Location* offset_point = new Location(*origin);

	//// TODO : When I put a print statement here for pitch, I get two strange numbers and a good number..why?
	//applyPitchToOffset(offset_point, orientation->pitch);
	//applyYawToOffset(offset_point, orientation->yaw);

	Quaternion pitch(Vector(1, 0, 0), orientation->pitch);
	Quaternion yaw(Vector(0, 0, 1), orientation->yaw);
	Quaternion roll(Vector(0, 1, 0), orientation->roll);

	Quaternion rotation_quaternion = roll * yaw * pitch;

	Vector rotation_vector = rotation_quaternion * Vector(0, 1, 0);

	// TODO : This is incredibly ugly
	Location offset_vector(offset_point->resolution, offset_point->unit, rotation_vector.x, rotation_vector.y, rotation_vector.z);

	offset_point = &(*offset_point + offset_vector);

	parameterize(offset_point);
}

ParamLine::~ParamLine()
{

}

// TODO : I don't think this handles negative angles yet
void ParamLine::applyPitchToOffset(Location* offset_point, double pitch)
{
	// Choose a random distance offset in meters to find our random second point on the line ("offset" point)

	/*
	            offset_point--->
					           / 
					         /  |
       random offset = 2m  /    |
			             /      |
		               /        |
	                 /          |
	pitch angle ---> ____________
					^
					|
				line origin
	
	*/

	double hypotenuse = 2;

	if (pitch < 0)
	{
		double adjacent = cos(rad(90 + pitch)) * hypotenuse;
		double opposite = sqrt(hypotenuse*hypotenuse - adjacent*adjacent);
		offset_point->meters_z = my_origin->meters_z - adjacent;
		offset_point->meters_y = my_origin->meters_y + opposite;
	} 
	else
	{
		double adjacent = cos(rad(pitch)) * hypotenuse;
		double opposite = sqrt(hypotenuse*hypotenuse - adjacent*adjacent);
		offset_point->meters_z = my_origin->meters_z + opposite;
		offset_point->meters_y = my_origin->meters_y + adjacent;
	}
	
}

void ParamLine::applyYawToOffset(Location* offset_point, double yaw)
{
	double circle_radius = offset_point->meters_y - my_origin->meters_y;
	double circle_angle;
	
	// My yaw 0 deg  points straight forward
	// but circle angle 0 points to the right
	if (yaw < 0)
	{
		circle_angle = 90 + abs(yaw); 
	}
	else {
		circle_angle = 90 - yaw;
	}

	offset_point->meters_x = my_origin->meters_x + (circle_radius * cos(rad(circle_angle)));
	offset_point->meters_y = my_origin->meters_y + (circle_radius * sin(rad(circle_angle)));
}

void ParamLine::parameterize(Location* offset_point)
{
	// r(t) = P + tD (P is vector touching line, D is direction vector
	// D = Q - P

	double D_x = offset_point->meters_x - my_origin->meters_x;
	double D_y = offset_point->meters_y - my_origin->meters_y;
	double D_z = offset_point->meters_z - my_origin->meters_z;

	my_param_x.first = my_origin->meters_x;
	my_param_x.second = D_x; // *t

	my_param_y.first = my_origin->meters_y;
	my_param_y.second = D_y; // *t

	my_param_z.first = my_origin->meters_z;
	my_param_z.second = D_z; // *t
}

std::pair<double, double> ParamLine::paramX()
{
	return my_param_x;
}

std::pair<double, double> ParamLine::paramY()
{
	return my_param_y;
}

std::pair<double, double> ParamLine::paramZ()
{
	return my_param_z;
}