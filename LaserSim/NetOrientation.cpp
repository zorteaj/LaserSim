#include "NetOrientation.h"

#include <thread>
#include <fstream>

#include "Object.h"
#include "Control.h"

int count = 0;

NetOrientation::NetOrientation(Object* object)
	: my_object(object), my_orientation(nullptr)
{
	std::ifstream port_config("portConfig.txt");
	int port;
	port_config >> port;
	Socket.Bind(port);

	// TODO: This has to be joined or terminated in the destructor perhaps
	task = new std::thread(&NetOrientation::listen, this);
}

NetOrientation::~NetOrientation()
{
	delete my_orientation;
}

void NetOrientation::listen()
{
	try
	{
		char packetBuffer[4];

		while (true)
		{
			//std::cout << "Listening..." << std::endl;

			sockaddr_in add = Socket.RecvFrom(packetBuffer, sizeof(packetBuffer));
			//std::cout << "recvied packet" << std::endl;

			delete my_orientation;

			int pitch = (int)packetBuffer[1];
			int adjusted_pitch = pitch * -1 + 90;

			int yaw = (int)packetBuffer[0];
			int adjusted_yaw = yaw + 90;

			if (count++ > 500)
			{
				//std::cout << "Adjusted yaw = " << adjusted_yaw << std::endl;
				//std::cout << "Yaw = " << yaw  << std::endl;
				count = 0;
			}

			// TODO: Get the order to be the same on both ends of the socket
			my_orientation = new Orientation(adjusted_pitch, adjusted_yaw, (int)packetBuffer[2]);

		}
	}
	catch (std::system_error& e)
	{
		std::cout << e.what();
	}
}

void NetOrientation::refresh()
{
	if (my_orientation != nullptr)
	{
		my_object->control()->onPitch(my_orientation->pitch, my_object);
		my_object->control()->onYaw(my_orientation->yaw, my_object);
		//my_object->control()->onRoll((int)packetBuffer[2], my_object);
	}
}

Orientation NetOrientation::orientation()
{
	return *my_orientation;
}