#pragma once
#include "Communicator.h"

class Server
{
private:
	Server() = default;  // no one else can create one
	~Server();
	Communicator* m_communicator = Communicator::get_instance();
public:
	static Server* get_instance();
	void run();
	static  Server* ptr;
};
