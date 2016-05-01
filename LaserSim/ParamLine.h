#pragma once

#include "Common.h"

#include <utility>

class ParamLine
{
public:
	// Constructor
	ParamLine(Location* origin, Orientation* orientation);
	
	// Destructor
	~ParamLine();

	// Apply pitch to offset
	void applyPitchToOffset(Location* offset_point, double pitch);

	// Apply yaw to offset
	void applyYawToOffset(Location* offset_point, double yaw);

	void parameterize(Location* offset_point);

	std::pair<double, double> paramX();

	std::pair<double, double> paramY();

	std::pair<double, double> paramZ();

private:
	Location* my_origin;
	Orientation* my_orientation;

	// second is *t
	std::pair<double, double> my_param_x; 
	std::pair<double, double> my_param_y;
	std::pair<double, double> my_param_z; 
};