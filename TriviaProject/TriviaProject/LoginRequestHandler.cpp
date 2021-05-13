#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "JsonResponsePacket.h"

LoginManager* LoginRequestHandler::m_loginManager =  m_loginManager->get_instance();
bool LoginRequestHandler::isRequestRelevant(RequestInfo info)
{
    return info.requestId == LOGIN_CODE || info.requestId == SIGNUP_CODE;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo info)
{
    RequestResult myResult;
    if (info.requestId == LOGIN_CODE)
    {
        myResult = login(info);
    }
    else if(info.requestId == SIGNUP_CODE)
    {
        myResult = signup(info);
    }
    else 
    {
        ErrorResponse response;
        response.message = ERROR;
        myResult.response = JsonResponsePacketSerializer::serializeResponse(response);
        myResult.newhandler = nullptr;
    }
    return myResult;
}

RequestResult LoginRequestHandler::login(RequestInfo info)
{
    RequestResult myResult;
    bool success = true;
    LoginResponse response;
    LoginRequest myRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(info.buffer);
    try
    {
        m_loginManager->login(myRequest.username, myRequest.password);
    }
    catch (...)
    {
        success = false;
        response.status = ERR_CODE;
        myResult.response = JsonResponsePacketSerializer::serializeResponse(response);
        myResult.newhandler = nullptr;
    }
    if (success)
    {
        myResult.newhandler = new MenuRequestHandler(myRequest.username);
        response.status = SUCCESS;
        myResult.response = JsonResponsePacketSerializer::serializeResponse(response);
    }
    return myResult;
}

RequestResult LoginRequestHandler::signup(RequestInfo info)
{
    RequestResult myResult;
    bool success = true;
    SignUpResponse response;
    SignupRequest myRequest = JsonRequestPacketDeserializer::deserializeSignupRequest(info.buffer);
    try
    {
        m_loginManager->signup(myRequest.username, myRequest.password, myRequest.email);
    }
    catch (...)
    {
        success = false;
        response.status = ERR_CODE;
        myResult.response = JsonResponsePacketSerializer::serializeResponse(response);
        myResult.newhandler = nullptr;
    }
    if (success)
    {
        myResult.newhandler = new MenuRequestHandler(myRequest.username);
        response.status = SUCCESS;
        myResult.response = JsonResponsePacketSerializer::serializeResponse(response);
    }
    return myResult;
}
