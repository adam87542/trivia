#pragma once
#include "LoginManager.h"
#include "LoginRequestHandler.h"

class RequestHandlerFactory
{
public:
	static RequestHandlerFactory* get_instance();
	static void reset_instance();
	LoginRequestHandler createLoginRequestHandler();

private:
	static  RequestHandlerFactory* m_ptr;
	RequestHandlerFactory() = default;
	~RequestHandlerFactory() = default;
};