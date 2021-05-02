#pragma once
#include "IRequestHandler.h"
#include "LoginManager.h"

class LoginRequestHandler : public IRequestHandler
{
public:
	bool isRequestRelevant(RequestInfo info) override;
	RequestResult handleRequest(RequestInfo info) override;
private:
	LoginManager* m_loginManager = m_loginManager->get_instance();
};

