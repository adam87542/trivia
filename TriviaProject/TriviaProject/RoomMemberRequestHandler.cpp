#include "RoomMemberRequestHandler.h"
#include "RequestHandlerFactory.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(string username, Room UserRoom)
{
	this->m_user = new LoggedUser(username);
	this->m_room = new Room(UserRoom);

}
bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo info)
{
	return info.requestId == LEAVE_ROOM_REQUEST || info.requestId == START_GAME_REQUEST || info.requestId == STATE_ROOM_REQUEST;
}

RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo info)
{
	RequestResult myResult;
	int code = info.requestId;
	switch (code)
	{
	case LEAVE_ROOM_REQUEST:
		myResult = LeaveGame();
		break;
	case  START_GAME_REQUEST:
		myResult = StartGame();
		break;
	case STATE_ROOM_REQUEST:
		myResult = GetRoomState();
		myResult.newhandler = RequestHandlerFactory::createRoomMemberRequestHandler(m_user->getUsername(), *m_room);
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
	return RoomAdminRequestHandler::StartGame(this->m_user->getUsername(), this->m_room->getData().difficulty, this->m_room->getAllUsers(), this->m_room->getData().id);
}

RequestResult RoomMemberRequestHandler::GetRoomState()
{
	return RoomAdminRequestHandler::GetRoomState(m_user->getUsername() , *m_room);
}


RequestResult RoomMemberRequestHandler::LeaveGame()
{
	RequestResult myResult;
	LeaveRoomResponse response;
	response.status = SUCCESS_CODE;
	myResult.newhandler = RequestHandlerFactory::createMenuRequestHandler(m_user->getUsername());
	myResult.response = JsonResponsePacketSerializer::serializeResponse(response);
	m_room->removeUser(*m_user);
	return myResult;
}
