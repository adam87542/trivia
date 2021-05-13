#pragma once
#include "IRequestHandler.h"


class RoomAdminRequestHandler : public IRequestHandler
{
	bool isRequestRelevant(RequestInfo info) override;
	RequestResult handleRequest(RequestInfo info) override;
};