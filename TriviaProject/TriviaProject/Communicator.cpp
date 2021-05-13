#include "Communicator.h"
#define PORT 25667
#define CODE_LENGTH 1
#define MSG_LENGTH 4

Communicator* Communicator::m_ptr = nullptr;
void Communicator::bindAndListen()
{
	struct sockaddr_in sa = { 0 };
	sa.sin_port = htons(PORT);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = INADDR_ANY;


	if (bind(m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port: " << PORT << std::endl;


}

void Communicator::handleNewClient(SOCKET clientSocket)
{
	RequestInfo recived;
	RequestResult res;
	res.response = (unsigned char*)"Hello";
	res.newhandler = RequestHandlerFactory::createLoginRequestHandler();
	Helper::sendData(clientSocket, std::string((char*)res.response));
	while (true)
	{
		try
		{
			recived = getMsgFromClient(clientSocket);
			res = PraseData(recived , res);
			Helper::sendData(clientSocket, std::string((char*)res.response));

			recived = getMsgFromClient(clientSocket);
			res = PraseData(recived , res);
			Helper::sendData(clientSocket, std::string((char*)res.response));
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			break;
		}
	}
}

RequestInfo Communicator::getMsgFromClient(SOCKET clientSocket)
{
	RequestInfo recived;
	//getting all msg
	recived.requestId = Helper::getIntPartFromSocket(clientSocket, CODE_LENGTH);
	int length = Helper::getIntPartFromSocket(clientSocket, MSG_LENGTH);
	recived.buffer = (unsigned char*)Helper::getPartFromSocket(clientSocket, length);
	return recived;
}

RequestResult Communicator::PraseData(RequestInfo recived , RequestResult res)
{
	if (!res.newhandler->isRequestRelevant(recived))
		recived.requestId = ERR_CODE;
	res = res.newhandler->handleRequest(recived);
	return res;
}

Communicator::Communicator()
{
	//Creating the server socket
	m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - creating socket failed");
}

Communicator::~Communicator()
{
	try
	{
		closesocket(m_serverSocket);
	}
	catch (...) {}
}

Communicator* Communicator::get_instance()
{
	if (!m_ptr)
	{
		m_ptr = new Communicator;
	}
	return m_ptr;
}

void Communicator::reset_instance()
{
	delete  m_ptr;
	m_ptr = nullptr;
}

void Communicator::startHandleRequests()
{
	
	bindAndListen();


	while (true)
	{
		std::cout << "Waiting for client connection request" << std::endl;
		// this accepts the client and create a specific socket from server to this client
		SOCKET client_socket = ::accept(m_serverSocket, NULL, NULL);

		if (client_socket == INVALID_SOCKET)
			throw std::exception(__FUNCTION__);
		IRequestHandler* handler = new LoginRequestHandler;
		std::pair<SOCKET, IRequestHandler*> currentClient(client_socket,handler);
		m_clients.insert(currentClient);
		std::cout << "Client accepted. Server and client can speak" << std::endl;

		// Creating the thread that will communicate with the user
		std::thread td(&Communicator::handleNewClient, this, client_socket);
		td.detach();
	}
}
