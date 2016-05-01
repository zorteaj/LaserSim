#pragma once

#include "Common.h"

class Scene;

class Converter {

private:
	Converter(Scene* scene);

public:
	static Converter* Create(Scene* scene);
	static Converter* Instance();
	~Converter();

	double unitMetersToPixels(double meters);
	double unitPixelsToMeters(double pixels);

	double coordMetersToPixelsX(ViewPointType type, double meters);
	double coordMetersToPixelsY(ViewPointType type, double meters);

	double coordPixelsToMetersX(ViewPointType type, double pixels);
	double coordPixelsToMetersY(ViewPointType type, double pixels);

private:
	static Converter* converter_instance;
	Scene* my_scene;
};