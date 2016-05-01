#pragma once

class Scene;
class Object;

class Control
{
public:
	Control(Object* object);

	static void onX(int x, void* obj);

	static void onY(int y, void* obj);

	static void onZ(int z, void* obj);

	static void onPitch(int pitch, void* obj);

	static void onYaw(int yaw, void* obj);

	static void onRoll(int roll, void* obj);

private:

	Scene* my_scene;

	static int my_slider_x_val;
	int my_slider_x_max;

	static int my_slider_y_val;
	int my_slider_y_max;

	static int my_slider_z_val;
	int my_slider_z_max;

	static int my_slider_pitch_val;
	int my_slider_pitch_max;

	static int my_slider_yaw_val;
	int my_slider_yaw_max;

	static int my_slider_roll_val;
	int my_slider_roll_max;

	static int my_factor;
};