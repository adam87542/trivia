#pragma comment (lib, "ws2_32.lib")


#include "WSAInitializer.h"
#include "Server.h"
#include <iostream>
#include <exception>
#define PORT 25667
int main()
{
	Server* myServer;
	try
	{
		WSAInitializer wsaInit;
	    myServer = myServer->get_instance();
		myServer->run();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	myServer->reset_instance();
	return 0;
}
