#pragma once
#include "IRequestHandler.h"
#include "GameManager.h"
#include "RoomManager.h"
#include "LoggedUser.h"
#include "JsonResponsePacket.h"

class GameRequestHandler : public IRequestHandler
{
private:
	Game* m_Game;
	LoggedUser* m_user;
	static GameManager* m_gameManager;
	static RoomManager* m_roomManager;
	RequestResult getQuestion(RequestInfo info);
	RequestResult submitAnswer(RequestInfo info);
	RequestResult getGameResults(RequestInfo info);
	RequestResult leaveGame(RequestInfo info);
public:
	GameRequestHandler(string username, string difficulty, std::vector<string> playersInRoom, unsigned int roomId);
	bool isRequestRelevant(RequestInfo info) override;
	RequestResult handleRequest(RequestInfo info) override;

};