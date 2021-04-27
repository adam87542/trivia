#pragma once
#include "IRequestHandler.h"
#include <iostream>
#include <map>
#include <WinSock2.h>
#include <Windows.h>

class Communicator
{
private:
	SOCKET m_serverSocket;
	std::map <SOCKET, IRequestHandler*> m_clients;
	void bindAndListen();
	void handleNewClient(SOCKET clientSocket);
public:
	void startHandleRequests();
	Communicator();
	~Communicator();
};

