#pragma once
#include "IRequestHandler.h"
#include "GameManager.h"
#include "RoomManager.h"
#include "Statistic_manager.h"
#include "LoggedUser.h"
#include "JsonResponsePacket.h"

class GameRequestHandler : public IRequestHandler
{
private:
	Game* m_Game;
	LoggedUser* m_user;
	std::vector<Question> m_questions;
	static GameManager* m_gameManager;
	static RoomManager* m_roomManager;
	static StatisticManager* m_statisticManager;
	RequestResult getQuestion(RequestInfo info);
	RequestResult submitAnswer(RequestInfo info);
	RequestResult getGameResults(RequestInfo info);
	RequestResult leaveGame(RequestInfo info);
	RequestResult GetHighScores(RequestInfo info);
public:
	GameRequestHandler(string username, string difficulty, std::vector<string> playersInRoom, unsigned int roomId , unsigned int numOfQuestions, std::vector<Question> questions);
	bool isRequestRelevant(RequestInfo info) override;
	RequestResult handleRequest(RequestInfo info) override;

};