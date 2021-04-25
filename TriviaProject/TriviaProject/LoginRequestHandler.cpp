#include "LoginRequestHandler.h"
#include "JsonResponsePacket.h"

bool LoginRequestHandler::isRequestRelevant(RequestInfo info)
{
    return info.requestId == LOGIN_CODE || info.requestId == SIGNUP_CODE;
}

Requestresult LoginRequestHandler::handleRequest(RequestInfo info)
{
    Requestresult myResult;
    if (info.requestId == LOGIN_CODE)
    {
        LoginRequest myRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(info.buffer);
        LoginResponse response;
        response.status = SUCCESS;
        myResult.response = JsonResponsePacketSerializer::serializeLoginResponse(response);
    }
    else
    {
        SignupRequest myRequest = JsonRequestPacketDeserializer::deserializeSignupRequest(info.buffer);
        SignUpResponse response;
        response.status = SUCCESS;
        myResult.response = JsonResponsePacketSerializer::serializeSignUpResponse(response);
    }

    return myResult;
}
