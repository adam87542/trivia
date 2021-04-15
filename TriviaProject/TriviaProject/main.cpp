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

		myServer.serve(25667);
	}
	catch (std::exception& e)
	{
		std::cout << "Error occured: " << e.what() << std::endl;
	}
	system("PAUSE");
	return 0;
	return 0;
}