#pragma once
#include "sr

class IRequestHandler
{
	virtual bool isRequestRelevant(RequestInfo info) = 0;
	virtual Requestresult handleRequest(RequestInfo info) = 0;
};

struct Requestresult
{
	unsigned char* response;
	IRequestHandler* newhandler;
};

