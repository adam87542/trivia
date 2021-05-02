#include "RequestHandlerFactory.h"

LoginRequestHandler RequestHandlerFactory::createLoginRequestHandler()
{
	LoginRequestHandler* login_request_handler = new LoginRequestHandler;
	return *login_request_handler;
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
	return this->m_loginManager;
}
