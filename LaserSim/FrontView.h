#pragma once

#include "ViewPoint2D.h"

#include "Common.h"

class Scene;
class LaserBeam;

/**
* FrontView, implements ViewPoint interface
*
* Represents view facing the target surface face
*
*/
class FrontView : public ViewPoint2D
{

public:
	// constuctor 
	FrontView(ViewPointType type, Scene* scene, std::string window_name, int width, int height);

	// Draws a beam endpoint (laser point) on the target surface, if the beam intersects the target surface
	virtual void projectBeam(ILDAPoint point);

	virtual void renderPlane(Plane* plane);

	virtual void renderProjector(Projector* projector);

	virtual void renderBeam(LaserBeam* beam);
};