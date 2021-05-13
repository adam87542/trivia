#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(string username)
{
	this->m_user = new LoggedUser(username);
}

bool MenuRequestHandler::isRequestRelevant(RequestInfo info)
{
	return (info.requestId == LOGOUT_CODE || info.requestId == GET_ROOMS_CODE || info.requestId == GET_PLAYERS_CODE || info.requestId == JOIN_ROOM_CODE || info.requestId == CREATE_ROOM_CODE || info.requestId == GET_HIGH_SCORES);
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo info)
{
	RequestResult myResult;
	int code = info.requestId;
	switch (code)
	{
	case LOGOUT_CODE:
		myResult = logout(info);
		break;
	case GET_ROOMS_CODE:
		myResult = getRooms(info);
		break;
	case GET_PLAYERS_CODE:
		myResult = getPlayersInRoom(info);
		break;
	case GET_HIGH_SCORES:
		myResult = getHighScore(info);
		break;
	case JOIN_ROOM_CODE:
		myResult = joinRoom(info);
		break;
	case CREATE_ROOM_CODE:
		myResult = createRoom(info);
		break;
	default:
		myResult.newhandler = nullptr;
		myResult.response = (unsigned char*)ERROR;
		break;
	}
	return myResult;
}

RequestResult MenuRequestHandler::logout(RequestInfo info)
{
	RequestResult myResult;
	LogoutResponse response;
	response.status = info.requestId;
	myResult.response = JsonResponsePacketSerializer::serializeResponse(response);
	myResult.newhandler = nullptr;
	return myResult;
}

RequestResult MenuRequestHandler::getRooms(RequestInfo info)
{
	RequestResult myResult;
	GetRoomsResponse respone;
	return RequestResult();
}

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo)
{
	return RequestResult();
}

RequestResult MenuRequestHandler::getPersonalStats(RequestInfo info)
{
	return RequestResult();
}

RequestResult MenuRequestHandler::getHighScore(RequestInfo info)
{
	return RequestResult();
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo info)
{
	return RequestResult();
}

RequestResult MenuRequestHandler::createRoom(RequestInfo info)
{
	return RequestResult();
}
