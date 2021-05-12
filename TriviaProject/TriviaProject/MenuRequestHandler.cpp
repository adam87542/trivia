#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(string username)
{
	this->m_user = new LoggedUser(username);
}

bool MenuRequestHandler::isRequestRelevant(RequestInfo info)
{
	return false;
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo info)
{
	return RequestResult();
}

RequestResult MenuRequestHandler::signout(RequestInfo info)
{
	return RequestResult();
}

RequestResult MenuRequestHandler::getRooms(RequestInfo info)
{
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
