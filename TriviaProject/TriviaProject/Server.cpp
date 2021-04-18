#include "Server.h"
#include <thread>
#include "WSAInitializer.h"

void Server::run()
{
	/*std::thread t_connector(&Communicator::startHandleRequests,&m_communicator);
	t_connector.detach();
	std::string input = "";
	
	while (input != "exit")
		std::cin >> input;	

	throw std::exception("Exited Server Succesfully");
*/
	WSAInitializer wsaInit;
	m_communicator.startHandleRequests();
}
