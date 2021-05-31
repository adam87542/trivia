#include "RoomAdminRequestHandler.h"
#include "RequestHandlerFactory.h"

RoomManager* RoomAdminRequestHandler::m_roomManager = RoomManager::get_instance();
RoomAdminRequestHandler::RoomAdminRequestHandler(string username , Room UserRoom)
{
		this->m_user = new LoggedUser(username);
		this->m_room = new Room(UserRoom);

}
bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo info)
{
	return info.requestId == CLOSE_ROOM_CODE || info.requestId == START_GAME_CODE || info.requestId == STATE_ROOM_CODE;
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo info)
{
	RequestResult myResult;
	int code = info.requestId;
	switch (code)
	{
	case CLOSE_ROOM_CODE:
		myResult = CloseRoom();
		break;
	case  START_GAME_CODE:
		myResult = StartGame();
		break;
	case STATE_ROOM_CODE:
		myResult = GetRoomState();
		break;
	default:
		myResult.newhandler = nullptr;
		myResult.response = (unsigned char*)ERROR;
		break;
	}
	return myResult;
}

RequestResult RoomAdminRequestHandler::CloseRoom()
{
	RequestResult myResult;
	CloseRoomResponse response;
	response.status = SUCCESS_CODE;
	myResult.response = JsonResponsePacketSerializer::serializeResponse(response);
	myResult.newhandler = RequestHandlerFactory::createMenuRequestHandler(m_user->getUsername());
	return myResult;
}

RequestResult RoomAdminRequestHandler::StartGame()
{
	RequestResult myResult;
	StartGameResponse response;
	response.status = SUCCESS_CODE;
	myResult.response = JsonResponsePacketSerializer::serializeResponse(response);
	return myResult;
}

RequestResult RoomAdminRequestHandler::GetRoomState()
{
	RequestResult myResult;
	GetRoomsResponse response;
	response.status = SUCCESS_CODE;
	response.rooms = m_roomManager->getRooms();
	myResult.response = JsonResponsePacketSerializer::serializeResponse(response);
	return myResult;
}
