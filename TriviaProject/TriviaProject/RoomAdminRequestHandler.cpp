#include "RoomAdminRequestHandler.h"
#include "RequestHandlerFactory.h"

RoomManager* RoomAdminRequestHandler::m_roomManager = RoomManager::getInstance();
RoomAdminRequestHandler::RoomAdminRequestHandler(string username , Room UserRoom)
{
		this->m_user = new LoggedUser(username);
		this->m_room = new Room(UserRoom);

}
bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo info)
{
	return info.requestId == CLOSE_ROOM_REQUEST || info.requestId == START_GAME_REQUEST || info.requestId == STATE_ROOM_REQUEST;
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo info)
{
	RequestResult myResult;
	int code = info.requestId;
	switch (code)
	{
	case CLOSE_ROOM_REQUEST:
		myResult = CloseRoom();
		break;
	case  START_GAME_REQUEST:
		myResult = StartGame(this->m_user->getUsername(), this->m_room->getData().difficulty, this->m_room->getAllUsers(), this->m_room->getData().id);
		myResult.newhandler = RequestHandlerFactory::createMenuRequestHandler(m_user->getUsername());
		break;
	case STATE_ROOM_REQUEST:
		myResult = GetRoomState(this->m_user->getUsername() ,*m_room);
		myResult.newhandler = RequestHandlerFactory::createRoomAdminRequestHandler(m_user->getUsername() , *m_room);
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
	myResult.newhandler = RequestHandlerFactory::createMenuRequestHandler(this->m_user->getUsername());
	m_roomManager->deleteRoom(m_room->getData().id);
	return myResult;
}

RequestResult RoomAdminRequestHandler::StartGame(string username, string difficulty, std::vector<string> playersInRoom, unsigned int roomId)
{
	RequestResult myResult;
	StartGameResponse response;
	response.status = SUCCESS_CODE;
	myResult.newhandler = RequestHandlerFactory::createGameRequestHandler(username, difficulty, playersInRoom, roomId);
	myResult.response = JsonResponsePacketSerializer::serializeResponse(response);
	return myResult;
}

RequestResult RoomAdminRequestHandler::GetRoomState(string username , Room room)
{
	RequestResult myResult;
	GetRoomStateResponse response;
	response.status = SUCCESS_CODE;
	response.hasGameBegun = room.getData().isActive;
	myResult.response = JsonResponsePacketSerializer::serializeResponse(response);
	myResult.newhandler = RequestHandlerFactory::createRoomAdminRequestHandler(username, room);
	return myResult;
}
