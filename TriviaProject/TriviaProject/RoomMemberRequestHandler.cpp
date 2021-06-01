#include "RoomMemberRequestHandler.h"
#include "RequestHandlerFactory.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(string username, Room UserRoom)
{
	this->m_user = new LoggedUser(username);
	this->m_room = new Room(UserRoom);

}
bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo info)
{
	return info.requestId == LEAVE_ROOM_CODE || info.requestId == START_GAME_CODE || info.requestId == STATE_ROOM_CODE;
}

RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo info)
{
	RequestResult myResult;
	int code = info.requestId;
	switch (code)
	{
	case LEAVE_ROOM_CODE:
		myResult = LeaveGame();
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
RequestResult RoomMemberRequestHandler::StartGame()
{
	return RoomAdminRequestHandler::StartGame();
}

RequestResult RoomMemberRequestHandler::GetRoomState()
{
	return RoomAdminRequestHandler::GetRoomState();
}


RequestResult RoomMemberRequestHandler::LeaveGame()
{
	RequestResult myResult;
	LeaveRoomResponse response;
	response.status = SUCCESS_CODE;
	myResult.response = JsonResponsePacketSerializer::serializeResponse(response);
	m_room->removeUser(*m_user);
	return myResult;
}
