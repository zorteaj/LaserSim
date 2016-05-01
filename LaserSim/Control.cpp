#include "Control.h"

#include "Controller.h"
#include "Scene.h"
#include "Converter.h"
#include "Object.h"

#include <iostream>

#include "opencv2/highgui/highgui.hpp"

int Control::my_factor = 2;

int Control::my_slider_x_val;
int Control::my_slider_y_val;
int Control::my_slider_z_val;

int Control::my_slider_pitch_val;
int Control::my_slider_yaw_val;
int Control::my_slider_roll_val;

Control::Control(Object* object)
{
	Converter* converter = Converter::Instance();

	cv::namedWindow(object->controller()->windowName(), cv::WINDOW_NORMAL);

	my_slider_x_val = object->location().meters_x * my_factor;
	my_slider_x_max = object->scene()->width() * my_factor;
	cv::createTrackbar((object->name() + " X").c_str(), object->controller()->windowName(), &my_slider_x_val, my_slider_x_max, onX, object);

	my_slider_y_val = object->location().meters_y * my_factor;
	my_slider_y_max = object->scene()->depth() * my_factor;
	cv::createTrackbar((object->name() + " Y").c_str(), object->controller()->windowName(), &my_slider_y_val, my_slider_y_max, onY, object);

	my_slider_z_val = object->location().meters_z * my_factor;
	my_slider_z_max = object->scene()->height() * my_factor;
	cv::createTrackbar((object->name() + " Z").c_str(), object->controller()->windowName(), &my_slider_z_val, my_slider_z_max, onZ, object);

	my_slider_pitch_val = object->orientation().pitch + 90;
	my_slider_pitch_max = 180;
	cv::createTrackbar((object->name() + " Pitch").c_str(), object->controller()->windowName(), &my_slider_pitch_val, my_slider_pitch_max, onPitch, object);

	my_slider_yaw_val = object->orientation().yaw + 90;
	my_slider_yaw_max = 180;
	cv::createTrackbar((object->name() + " Yaw").c_str(), object->controller()->windowName(), &my_slider_yaw_val, my_slider_yaw_max, onYaw, object);

	my_slider_roll_val = object->orientation().roll + 90;
	my_slider_roll_max = 180;
	cv::createTrackbar((object->name() + " Roll").c_str(), object->controller()->windowName(), &my_slider_roll_val, my_slider_roll_max, onRoll, object);

	onX(my_slider_x_val, object);
	onY(my_slider_y_val, object);
	onZ(my_slider_z_val, object);

	onPitch(my_slider_pitch_val, object);
	onYaw(my_slider_yaw_val, object);
	onRoll(my_slider_roll_val, object);
}

void Control::onX(int x, void* obj)
{
	Object* object = static_cast<Object*>(obj);
	object->setLocation(Location(object->scene()->resolution(), Location::METERS, (double)x / my_factor, object->location().meters_y, object->location().meters_z));
	object->scene()->refresh();
}

void Control::onY(int y, void* obj)
{
	Object* object = static_cast<Object*>(obj);
	object->setLocation(Location(object->scene()->resolution(), Location::METERS, object->location().meters_x, (double)y / my_factor, object->location().meters_z));
	object->scene()->refresh();
}

void Control::onZ(int z, void* obj)
{
	Object* object = static_cast<Object*>(obj);
	object->setLocation(Location(object->scene()->resolution(), Location::METERS, object->location().meters_x, object->location().meters_y, (double)z / my_factor));
	object->scene()->refresh();
}

void Control::onPitch(int pitch, void* obj)
{
	//std::cout << "Pitch = " << pitch << std::endl;
	Object* object = static_cast<Object*>(obj);
	object->setOrientation(Orientation(pitch - 90, object->orientation().yaw, object->orientation().roll));
	object->scene()->refresh();
}

void Control::onYaw(int yaw, void* obj)
{
	// std::cout << "Yaw = " << yaw << std::endl;
	Object* object = static_cast<Object*>(obj);
	object->setOrientation(Orientation(object->orientation().pitch, yaw - 90, object->orientation().roll));
	object->scene()->refresh();
}

void Control::onRoll(int roll, void* obj)
{
	// std::cout << "Roll = " << roll << std::endl;
	Object* object = static_cast<Object*>(obj);
	object->setOrientation(Orientation(object->orientation().pitch, object->orientation().yaw, roll-90));
	object->scene()->refresh();
}