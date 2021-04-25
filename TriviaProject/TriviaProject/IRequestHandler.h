#pragma once
#include "Structs.h"

struct RequestResult;
struct RequestInfo;

class IRequestHandler
{
	virtual bool isRequestRelevant(RequestInfo info) = 0;
	virtual RequestResult handleRequest(RequestInfo info) = 0;
};
