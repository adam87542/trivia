#pragma once
#include "Response.h"

class IRequestHandler
{
	virtual bool isRequestRelevant(RequestInfo info) = 0;
	virtual Requestresult handleRequest(RequestInfo info) = 0;
};

struct Requestresult
{
	unsigned char* buffer;
	IRequestHandler* newhandler;
};

