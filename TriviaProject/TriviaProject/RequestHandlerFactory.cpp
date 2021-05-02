#include "RequestHandlerFactory.h"
RequestHandlerFactory* RequestHandlerFactory::ptr = nullptr;
RequestHandlerFactory::~RequestHandlerFactory()
{
	delete this->m_database;
	delete ptr;
}

RequestHandlerFactory::RequestHandlerFactory()
{
	this->m_database = new SqliteDataBase;
}
LoginRequestHandler RequestHandlerFactory::createLoginRequestHandler()
{
	LoginRequestHandler* login_request_handler = new LoginRequestHandler;
	return *login_request_handler;
}

LoginManager* RequestHandlerFactory::getLoginManager()
{
	return this->m_loginManager;
}

RequestHandlerFactory* RequestHandlerFactory::get_instance()
{
	if (!ptr)
		ptr = new RequestHandlerFactory;
	return ptr;
}
