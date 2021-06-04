#pragma once
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "RoomAdminRequestHandler.h"

class RequestHandlerFactory
{
public:
	static RequestHandlerFactory* get_instance();
	static void reset_instance();
	static LoginRequestHandler* createLoginRequestHandler();
	static MenuRequestHandler* createMenuRequestHandler(string username);
	static RoomAdminRequestHandler* createRoomAdminRequestHandler(string username, Room UserRoom);
	static RoomMemberRequestHandler* createRoomMemberRequestHandler(string username, Room UserRoom);
private:
	static  RequestHandlerFactory* m_ptr;
	RequestHandlerFactory() = default;
	~RequestHandlerFactory() = default;
};