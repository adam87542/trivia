#pragma once
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "IDatabase.h"

class RequestHandlerFactory
{
public:
	static RequestHandlerFactory* get_instance();
	static  RequestHandlerFactory* ptr;
	LoginRequestHandler createLoginRequestHandler();
	LoginManager* getLoginManager();

private:
	IDatabase* m_database;
	LoginManager* m_loginManager = m_loginManager->get_instance();
	RequestHandlerFactory();
	~RequestHandlerFactory();
};