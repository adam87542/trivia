#pragma once
#include "IRequestHandler.h"


class RoomMemberRequestHandler : public IRequestHandler
{
	bool isRequestRelevant(RequestInfo info) override;
	RequestResult handleRequest(RequestInfo info) override;
};