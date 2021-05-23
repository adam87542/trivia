#pragma once
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"

class RequestHandlerFactory
{
public:
	static RequestHandlerFactory* get_instance();
	static void reset_instance();
	static LoginRequestHandler* createLoginRequestHandler();
	static MenuRequestHandler* createMenuRequestHandler(string username);
	static RoomAdminRequestHandler* createRoomAdminRequestHandler();
	static RoomMemberRequestHandler* createRoomMemberRequestHandler();
private:
	static  RequestHandlerFactory* m_ptr;
	RequestHandlerFactory() = default;
	~RequestHandlerFactory() = default;
};