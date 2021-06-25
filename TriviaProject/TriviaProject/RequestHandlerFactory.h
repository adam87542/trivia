#pragma once
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "GameRequestHandler.h"

class RequestHandlerFactory
{
public:
	static RequestHandlerFactory* get_instance();
	static void reset_instance();
	static LoginRequestHandler* createLoginRequestHandler();
	static MenuRequestHandler* createMenuRequestHandler(string username);
	static RoomAdminRequestHandler* createRoomAdminRequestHandler(string username, Room UserRoom);
	static RoomMemberRequestHandler* createRoomMemberRequestHandler(string username, Room UserRoom);
	static GameRequestHandler* createGameRequestHandler(string username, string difficulty, std::vector<string> playersInRoom, unsigned int roomId);
private:
	static  RequestHandlerFactory* m_ptr;
	RequestHandlerFactory() = default;
	~RequestHandlerFactory() = default;
};