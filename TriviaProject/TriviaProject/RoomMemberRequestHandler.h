#pragma once
#include "IRequestHandler.h"
#include "LoggedUser.h"
#include "JsonResponsePacket.h"
#include "RoomManager.h"
#include "GameManager.h"
#include "IDatabase.h"


class RoomMemberRequestHandler : public IRequestHandler
{
public:
	RoomMemberRequestHandler(string username, Room UserRoom);
	bool isRequestRelevant(RequestInfo info) override;
	RequestResult handleRequest(RequestInfo info) override;
private:
	static RoomManager* m_roomManager;
	static GameManager* m_GameManager;
	Room* m_room;
	LoggedUser* m_user;
	static IDatabase* m_dataBase;
	RequestResult StartGame();
	RequestResult GetRoomState();
	RequestResult LeaveGame();
};