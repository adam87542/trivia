#pragma once
#include "RoomMemberRequestHandler.h"

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
	static GameManager* m_gameManager;
	static IDatabase* m_dataBase;
	RequestResult CloseRoom();
	 RequestResult StartGame();
	static RequestResult getPlayersInRoom(RequestInfo info, bool isMember, string username, Room room);
	friend class RoomMemberRequestHandler;
};