#include "GameRequestHandler.h"
#include "RequestHandlerFactory.h"

GameManager* GameRequestHandler::m_gameManager = GameManager::getInstance();
RoomManager* GameRequestHandler::m_roomManager = RoomManager::getInstance();
bool GameRequestHandler::isRequestRelevant(RequestInfo info)
{

}

RequestResult GameRequestHandler::handleRequest(RequestInfo info)
{
	return RequestResult();
}


RequestResult GameRequestHandler::getQuestion(RequestInfo info)
{
	return RequestResult();
}

RequestResult GameRequestHandler::submitAnswer(RequestInfo info)
{
	return RequestResult();
}

RequestResult GameRequestHandler::getGameResults(RequestInfo info)
{
	return RequestResult();
}

RequestResult GameRequestHandler::leaveGame(RequestInfo info)
{
	return RequestResult();
}

GameRequestHandler::GameRequestHandler(string username, string difficulty, std::vector<string> playersInRoom, unsigned int roomId)
{
	this->m_Game = new Game(difficulty, playersInRoom, roomId);
	this->m_user = new LoggedUser(username);
	m_gameManager->createGame(this->m_Game);
}
