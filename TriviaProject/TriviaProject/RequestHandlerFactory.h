#pragma once
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "IDatabase.h"
class LoginRequestHandler;

class RequestHandlerFactory
{
public:
	LoginRequestHandler createLoginRequestHandler();
	LoginManager& getLoginManager();
private:
	IDatabase* m_database;
	LoginManager m_loginManager;
};