#pragma once
#include "IRequestHandler.h"
#include "LoggedUser.h"
#include "JsonResponsePacket.h"
#include "Statistic_manager.h"
#include "RoomManager.h"
#include "LoginManager.h"

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(string username);
	bool isRequestRelevant(RequestInfo info) override;
	RequestResult handleRequest(RequestInfo info) override;
private:
	LoggedUser* m_user;
	static StatisticManager* m_statisticManager;
	static RoomManager* m_roomManager;
	static LoginManager* m_loginManager;
	RequestResult logout(RequestInfo info);
	RequestResult getRooms(RequestInfo info);
	RequestResult getPlayersInRoom(RequestInfo);
	//RequestResult getPersonalStats(RequestInfo info);
	RequestResult getHighScore(RequestInfo info);
	RequestResult joinRoom(RequestInfo info);
	RequestResult createRoom(RequestInfo info);

	bool IsIdExists(int id);
	string FromVecToString(std::vector<std::pair<string, int>> vec);
	string FromUserStatisticsToString(UserStatistics statistics);
};
