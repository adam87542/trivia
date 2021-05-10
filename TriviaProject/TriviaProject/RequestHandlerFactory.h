#pragma once
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"

class RequestHandlerFactory
{
public:
	static RequestHandlerFactory* get_instance();
	static void reset_instance();
	LoginRequestHandler createLoginRequestHandler();
	MenuRequestHandler createMenuRequestHandler();
private:
	static  RequestHandlerFactory* m_ptr;
	RequestHandlerFactory() = default;
	~RequestHandlerFactory() = default;
};