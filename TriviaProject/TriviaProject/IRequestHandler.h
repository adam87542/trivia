#pragma once
#include "Structs.h"

class IRequestHandler
{
	virtual bool isRequestRelevant(RequestInfo info) = 0;
	virtual Requestresult handleRequest(RequestInfo info) = 0;
};
