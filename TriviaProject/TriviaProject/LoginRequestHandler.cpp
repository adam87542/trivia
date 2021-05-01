#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "JsonResponsePacket.h"
bool LoginRequestHandler::isRequestRelevant(RequestInfo info)
{
    return info.requestId == LOGIN_CODE || info.requestId == SIGNUP_CODE;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo info)
{
    bool success = true;
    RequestResult myResult;
    if (info.requestId == LOGIN_CODE)
    {
        LoginResponse response;
        LoginRequest myRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(info.buffer);
        try
        {
          m_loginManager.login(myRequest.username, myRequest.password);
        }
        catch (...)
        {
            success = false;
            response.status = ERR_CODE;
            myResult.response = JsonResponsePacketSerializer::serializeLoginResponse(response);
            myResult.newhandler = nullptr;
        }
        if (success)
        {
            myResult.newhandler = new MenuRequestHandler;
            response.status = SUCCESS;
            myResult.response = JsonResponsePacketSerializer::serializeLoginResponse(response);
        }
    }
    else if(info.requestId == SIGNUP_CODE)
    {
        SignUpResponse response;
        SignupRequest myRequest = JsonRequestPacketDeserializer::deserializeSignupRequest(info.buffer);
        try
        {
           m_loginManager.signup(myRequest.username, myRequest.password , myRequest.email);
        }
        catch (...)
        {
            success = false;
            response.status = ERR_CODE;
            myResult.response = JsonResponsePacketSerializer::serializeSignUpResponse(response);
            myResult.newhandler = nullptr;
        }
        if (success)
        {
            myResult.newhandler = new MenuRequestHandler;
            response.status = SUCCESS;
            myResult.response = JsonResponsePacketSerializer::serializeSignUpResponse(response);
        }
    }
    else if(info.requestId == ERR_CODE)
    {
        ErrorResponse response;
        response.message = "Bad request...";
        myResult.response = JsonResponsePacketSerializer::serializeErrorResponse(response);
        myResult.newhandler = nullptr;
    }
    return myResult;
}
