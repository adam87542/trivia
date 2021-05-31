#pragma once
#include "IRequestHandler.h"
#include "LoggedUser.h"
#include "JsonResponsePacket.h"
#include "RoomManager.h"

class RoomAdminRequestHandler : public IRequestHandler
{
public:
	RoomAdminRequestHandler(string username, Room UserRoom);
	bool isRequestRelevant(RequestInfo info) override;
	RequestResult handleRequest(RequestInfo info) override;
private:
	Room* m_room;
	LoggedUser* m_user;
	static RoomManager* m_roomManager;
	RequestResult CloseRoom();
	RequestResult StartGame();
	RequestResult GetRoomState();
};