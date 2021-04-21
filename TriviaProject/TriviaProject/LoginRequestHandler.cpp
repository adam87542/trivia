#include "LoginRequestHandler.h"
#include "JsonResponsePacket.h"

bool LoginRequestHandler::isRequestRelevant(RequestInfo info)
{
    return info.requestId == LOGIN_RESPONSE || info.requestId == SIGNUP_RESPONSE;
}

Requestresult LoginRequestHandler::handleRequest(RequestInfo info)
{
    Requestresult myResult;
    if (info.requestId == LOGIN_RESPONSE)
    {
        LoginRequest myRequest = JsonRequestPacketDeserializer::DeserializeLoginRequest(info.buffer);
        LoginResponse response;
        response.status = SUCCESS;
        myResult.response = JsonResponsePacketSerializer::serializeLoginResponse(response);
    }
    else
    {
        SignupRequest myRequest = JsonRequestPacketDeserializer::DeserializeSignupRequest(info.buffer);
        SignUpResponse response;
        response.status = SUCCESS;
        myResult.response = JsonResponsePacketSerializer::serializeSignUpResponse(response);
    }

    return myResult;
}
