#pragma once
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"
#include "Helper.h"
#include "JsonResponsePacket.h"
#include <iostream>
#include <map>
#include <WinSock2.h>
#include <Windows.h>
#include <thread>

class Communicator
{
private:
	static  Communicator* m_ptr;
	Communicator();
	~Communicator();
	SOCKET m_serverSocket;
	std::map <SOCKET, IRequestHandler*> m_clients;
	void bindAndListen();
	void handleNewClient(SOCKET clientSocket);
public:
	static Communicator* get_instance();
	static void reset_instance();
	void startHandleRequests();
};

