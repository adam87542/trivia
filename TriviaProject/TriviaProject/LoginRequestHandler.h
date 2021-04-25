#pragma once
#include "IRequestHandler.h"

class LoginRequestHandler : public IRequestHandler
{
public:
	bool isRequestRelevant(RequestInfo info) override;
	Requestresult handleRequest(RequestInfo info) override;
};

