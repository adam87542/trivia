#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
public:
	bool isRequestRelevant(RequestInfo info) override;
	RequestResult handleRequest(RequestInfo info) override;
private:
	LoginManager m_loginManager;
	//RequestHandlerFactory m_handlerFactory;
};

