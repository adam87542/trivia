#pragma once
#include <map> 
#include "IRequestHandler.h"
#include <iostream>
#include <WinSock2.h>


class Communicator
{
private:
	SOCKET m_serverSocket;
	std::map <SOCKET, IRequestHandler> m_clients;
	void bindAndListen();
	void handleNewClient(SOCKET clientSocket);
public:
	Communicator();
	~Communicator();
	void startHandleRequests();

};

