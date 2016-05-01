#pragma once

#include "ViewPoint2D.h"

class Projector;
class LaserBeam;

/**
* SideView, implements ViewPoint interface
*
* Represents view facing the target surface side
*
*/
class SideView : public ViewPoint2D
{

public:
	// Constuctor 
	SideView(ViewPointType type, Scene* scene, std::string window_name, int width, int height);

	// Draws a beam endpoint (laser point) on the target surface, if the beam intersects the target surface
	virtual void projectBeam(ILDAPoint point);

	virtual void renderPlane(Plane* plane);

	virtual void renderProjector(Projector* projector);
	
	virtual void renderBeam(LaserBeam* beam);
};