#include "LoginRequestHandler.h"
#include "JsonResponsePacket.h"
#include "RequestHandlerFactory.h"

LoginManager* LoginRequestHandler::m_loginManager =  m_loginManager->get_instance();
bool LoginRequestHandler::isRequestRelevant(RequestInfo info)
{
    return info.requestId == LOGIN_REQUEST || info.requestId == SIGNUP_REQUEST;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo info)
{
    RequestResult myResult;
    if (info.requestId == LOGIN_REQUEST)
    {
        myResult = login(info);
    }
    else if(info.requestId == SIGNUP_REQUEST)
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
        myResult.newhandler = RequestHandlerFactory::createLoginRequestHandler();
    }
    if (success)
    {
        myResult.newhandler = RequestHandlerFactory::createMenuRequestHandler(myRequest.username);
        response.status = SUCCESS_CODE;
        myResult.response = JsonResponsePacketSerializer::serializeResponse(response);
    }
    return myResult;
}

RequestResult LoginRequestHandler::signup(RequestInfo info)
{
    RequestResult myResult;
    ErrorResponse error;
    bool success = true;
    SignUpResponse response;
    SignupRequest myRequest = JsonRequestPacketDeserializer::deserializeSignupRequest(info.buffer);
    try
    {
        m_loginManager->signup(myRequest.username, myRequest.password, myRequest.email);
    }
    catch (const std::exception e)
    {
        success = false;
        error.message = e.what();
        myResult.newhandler = RequestHandlerFactory::createLoginRequestHandler();
        myResult.response = JsonResponsePacketSerializer::serializeResponse(error);
    }
    if (success)
    {
        myResult.newhandler = RequestHandlerFactory::createMenuRequestHandler(myRequest.username);
        response.status = SUCCESS_CODE;
        myResult.response = JsonResponsePacketSerializer::serializeResponse(response);
    }
    return myResult;
}
