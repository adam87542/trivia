#pragma comment (lib, "ws2_32.lib")


#include "WSAInitializer.h"
#include "Server.h"
#include <iostream>
#include <exception>
#undef main
int main()
{
	try
	{
		WSAInitializer wsaInit;
		Server myServer;
		myServer.run();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}