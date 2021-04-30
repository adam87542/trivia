#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "JsonResponsePacket.h"
bool LoginRequestHandler::isRequestRelevant(RequestInfo info)
{
    return info.requestId == LOGIN_CODE || info.requestId == SIGNUP_CODE;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo info)
{
    RequestResult myResult;
    if (info.requestId == LOGIN_CODE)
    {
        LoginRequest myRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(info.buffer);
        LoginResponse response;
        myResult.newhandler = new MenuRequestHandler;
        response.status = SUCCESS;
        myResult.response = JsonResponsePacketSerializer::serializeLoginResponse(response);
    }
    else if(info.requestId == SIGNUP_CODE)
    {
        SignupRequest myRequest = JsonRequestPacketDeserializer::deserializeSignupRequest(info.buffer);
        SignUpResponse response;
        myResult.newhandler = new MenuRequestHandler;
        response.status = SUCCESS;
        myResult.response = JsonResponsePacketSerializer::serializeSignUpResponse(response);
    }
    else
    {
        myResult.response = FAILED;
        myResult.newhandler = nullptr;
    }
    return myResult;
}
