#include "RequestHandlerFactory.h"
#include "SqliteDataBase.h"
RequestHandlerFactory* RequestHandlerFactory::m_ptr = nullptr;


LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	LoginRequestHandler* loginRequestHandler = new LoginRequestHandler;
	return loginRequestHandler;
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(string username)
{
	MenuRequestHandler* menuRequestHandler = new MenuRequestHandler(username);
	return menuRequestHandler;
}

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(string username, Room UserRoom)
{
	RoomAdminRequestHandler* roomAdminRequestHandler = new RoomAdminRequestHandler(username , UserRoom);
	return roomAdminRequestHandler;
}

RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(string username, Room UserRoom)
{
	RoomMemberRequestHandler* roomMemberRequestHandler = new RoomMemberRequestHandler(username, UserRoom);
	return roomMemberRequestHandler;
}

RequestHandlerFactory* RequestHandlerFactory::get_instance()
{
	if (!m_ptr)
	{
		m_ptr = new RequestHandlerFactory;
	}
	return m_ptr;
}

void RequestHandlerFactory::reset_instance()
{
	delete m_ptr;
	m_ptr = nullptr;
}
