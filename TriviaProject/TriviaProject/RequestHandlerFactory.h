#pragma once
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "IDatabase.h"

class RequestHandlerFactory
{
public:
	static RequestHandlerFactory* get_instance();
	static void reset_instance();
	LoginRequestHandler createLoginRequestHandler();
	LoginManager* getLoginManager();

private:
	static  RequestHandlerFactory* m_ptr;
	static IDatabase* m_database;
	static LoginManager* m_loginManager;
	RequestHandlerFactory();
	~RequestHandlerFactory();
};