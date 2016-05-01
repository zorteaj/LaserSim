#include "ParamLine.h"
#include "Utils.h"

#include "quaternion.h"

#include <iostream>

ParamLine::ParamLine(Location* origin, Orientation* orientation) : my_origin(origin)
{
	Location* offset_point = new Location(*origin);

	Quaternion pitch(Vector(1, 0, 0), orientation->pitch);
	Quaternion yaw;
	// For the unit circle, positive angles are counter-clockwise roations,
	// but in this program's paradigm, negative angles are left (counter-clockwise) rotations
	if (orientation->yaw < 0)
	{
		yaw = Quaternion(Vector(0, 0, 1), abs(orientation->yaw));
	}
	else
	{
		yaw = Quaternion(Vector(0, 0, 1), 360 - orientation->yaw);
	}
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