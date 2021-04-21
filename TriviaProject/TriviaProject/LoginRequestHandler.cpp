#include "LoginRequestHandler.h"
#include "JsonResponsePacket.h"

bool LoginRequestHandler::isRequestRelevant(RequestInfo info)
{
    return info.RequestId == LOGIN_RESPONSE || info.RequestId == SIGNUP_RESPONSE;
}

Requestresult LoginRequestHandler::handleRequest(RequestInfo info)
{
    Requestresult* result = new Requestresult;
    if (!isRequestRelevant(info))
    {
        result = nullptr;
    }
    else
    {
        result->buffer = info.buffer;
        result->newhandler = new LoginRequestHandler;
    }
    return *result;
}
