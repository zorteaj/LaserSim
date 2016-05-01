#include "Converter.h"

#include "Scene.h"

Converter* Converter::converter_instance = nullptr;

Converter::Converter(Scene* scene) : my_scene(scene) {

}

Converter* Converter::Create(Scene* scene)
{
	if (!converter_instance) {
		converter_instance = new Converter(scene);
	}
	return converter_instance;
}

Converter* Converter::Instance()
{
	return converter_instance;
}

Converter::~Converter()
{
	delete converter_instance;
}

double Converter::unitMetersToPixels(double meters)
{
	return meters * my_scene->resolution();
}

double Converter::unitPixelsToMeters(double pixels)
{
	return pixels / my_scene->resolution();;
}

double Converter::coordMetersToPixelsX(ViewPointType type, double meters) 
{
	return unitMetersToPixels(meters);
}

double Converter::coordMetersToPixelsY(ViewPointType type, double meters)
{
	// TODO: Perhaps these should be members of the ViewPoint2D
	int view_width; // Mat pixels
	//int view_height; // Mat pixels

	if (type == FRONT)
	{
		view_width = unitMetersToPixels(my_scene->depth());
	}
	else if (type == SIDE)
	{
		view_width = unitMetersToPixels(my_scene->width());
	}

	return view_width - unitMetersToPixels(meters);
}

double Converter::coordPixelsToMetersX(ViewPointType type, double pixels)
{
	return -1; // TODO: Implement if needed or discard
}

double Converter::coordPixelsToMetersY(ViewPointType type, double pixels)
{
	return -1; // TODO: Implement if needed or discard
}
