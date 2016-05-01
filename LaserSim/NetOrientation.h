#include "Network.h"

#include "Common.h"
#include <thread>

class Object;

class NetOrientation {
public:
	// Constructor 
	NetOrientation(Object* object);

	// Destructor
	~NetOrientation();

	// Listen for orientation updates
	void listen();

	void refresh();

	// Get Orientation
	Orientation orientation();

private:
	Orientation* my_orientation;

	// The Object whose Orientation this object controls
	Object* my_object;

	WSASession Session;

	UDPSocket Socket;

	std::thread* task;

};

