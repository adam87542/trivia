#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <string>
#include <vector>
#include <queue>
#include <mutex>


class Server
{
public:
	Server();
	~Server();
	void serve(int port);

private:
	SOCKET _serverSocket;
	void accept();
	void clientHandler(SOCKET clientSocket);
};
