#pragma once

#include "SideView.h"
#include "FrontView.h"

/**
* ViewPointFactory
*
* Convenience utilityi for creating viewpoints
*
*/
class ViewPointFactory
{
public:

	static ViewPoint2D* create(ViewPointType type, Scene* scene,  int resolution, int width, int height, int depth)
	{
		// Index appended to each ViewPoint to form a unique name
		// Incrememted with each new ViewPoint of the given type
		static int side_count;
		static int front_count = 0;

		switch (type)
		{
		case ViewPointType::SIDE: 
			side_count++;
			return new SideView(type, scene, std::string("SIDE " + std::to_string(side_count)), depth, height);
			break;
		case ViewPointType::FRONT:
			front_count++;
			return new FrontView(type, scene, std::string("FRONT " + std::to_string(front_count)), width, height);
			break;
		}
	}
};
