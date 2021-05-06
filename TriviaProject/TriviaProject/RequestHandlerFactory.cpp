#include "RequestHandlerFactory.h"
#include "SqliteDataBase.h"
RequestHandlerFactory* RequestHandlerFactory::m_ptr = nullptr;


LoginRequestHandler RequestHandlerFactory::createLoginRequestHandler()
{
	LoginRequestHandler* login_request_handler = new LoginRequestHandler;
	return *login_request_handler;
}

RequestHandlerFactory* RequestHandlerFactory::get_instance()
{
	if (!m_ptr)
	{
		m_ptr = new RequestHandlerFactory;
	}
	return m_ptr;
}

void RequestHandlerFactory::reset_instance()
{
	delete m_ptr;
	m_ptr = nullptr;
}
