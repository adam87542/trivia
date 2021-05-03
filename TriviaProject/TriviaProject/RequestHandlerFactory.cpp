#include "RequestHandlerFactory.h"
RequestHandlerFactory* RequestHandlerFactory::m_ptr = nullptr;
IDatabase* RequestHandlerFactory::m_database = nullptr;
LoginManager* RequestHandlerFactory::m_loginManager = nullptr;


LoginRequestHandler RequestHandlerFactory::createLoginRequestHandler()
{
	LoginRequestHandler* login_request_handler = new LoginRequestHandler;
	return *login_request_handler;
}

LoginManager* RequestHandlerFactory::getLoginManager()
{
	return this->m_loginManager;
}

RequestHandlerFactory::~RequestHandlerFactory()
{
	delete m_database;
	m_database = nullptr;
	m_loginManager->reset_instance();
	m_loginManager = nullptr;
}
RequestHandlerFactory::RequestHandlerFactory()
{
	m_database = new SqliteDataBase;
	m_loginManager = m_loginManager->get_instance();
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
