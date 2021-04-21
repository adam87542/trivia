#pragma once
#include "IRequestHandler.h"

class LoginRequestHandler : public IRequestHandler
{
	bool isRequestRelevant(RequestInfo info) override;
	Requestresult handleRequest(RequestInfo info) override;
};

