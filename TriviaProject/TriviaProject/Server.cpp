#include "Server.h"
#include <thread>
#include "WSAInitializer.h"

Server* Server::ptr = nullptr;
Server::~Server()
{
	delete this->ptr;
}
Server* Server::get_instance()
{
	if (!ptr)
		ptr = new Server;
	return ptr;
}

void Server::run()
{
	std::thread t_connector(&Communicator::startHandleRequests,this->m_communicator);
	std::string input = "";
	t_connector.detach();

	while (input != "exit")
		std::cin >> input;	

	t_connector.~thread();
	std::cout << "Exited Server Succesfully" << std::endl;


}
