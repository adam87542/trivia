#include "RoomMemberRequestHandler.h"
#include "RequestHandlerFactory.h"

RoomManager* RoomMemberRequestHandler::m_roomManager = RoomManager::get_instance();
IDatabase* RoomMemberRequestHandler::m_dataBase = SqliteDataBase::get_instance();
GameManager* RoomMemberRequestHandler::m_GameManager = GameManager::getInstance();
RoomMemberRequestHandler::RoomMemberRequestHandler(string username, Room UserRoom)
{
	this->m_user = new LoggedUser(username);
	this->m_room = new Room(UserRoom);

}
bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo info)
{
	return info.requestId == LEAVE_ROOM_REQUEST || info.requestId == START_GAME_REQUEST || info.requestId == STATE_ROOM_REQUEST || info.requestId == GET_PLAYERS_REQUEST;
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
		break;
	case GET_PLAYERS_REQUEST:
		myResult = RoomAdminRequestHandler::getPlayersInRoom(info , true , this->m_user->getUsername() , *m_room);
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
	RequestResult myResult;
	StartGameResponse response;
	response.status = SUCCESS_CODE;
	myResult.response = JsonResponsePacketSerializer::serializeResponse(response);
	myResult.newhandler = RequestHandlerFactory::createGameRequestHandler(this->m_user->getUsername(), this->m_room->getData().id , NULL);
	return myResult;
}

RequestResult RoomMemberRequestHandler::GetRoomState()
{
	RequestResult myResult;
	GetRoomStateResponse response;
	response.status = SUCCESS_CODE;
	try
	{
		response.hasGameBegun = m_roomManager->GetRoomById(this->m_room->getData().id).getData().isGameBegan;
	}
	catch(const std::exception e)
	{
		response.hasGameBegun = false;
	}
	myResult.response = JsonResponsePacketSerializer::serializeResponse(response);
	myResult.newhandler = RequestHandlerFactory::createRoomMemberRequestHandler(this->m_user->getUsername(), *m_room);
	return myResult;
}
RequestResult RoomMemberRequestHandler::LeaveGame()
{
	RequestResult myResult;
	LeaveRoomResponse response;
	m_roomManager->removePlayerFromRoom(this->m_room->getData().id, this->m_user->getUsername());
	myResult.newhandler = RequestHandlerFactory::createMenuRequestHandler(m_user->getUsername());
	response.status = SUCCESS_CODE;
	myResult.response = JsonResponsePacketSerializer::serializeResponse(response);
	return myResult;
}
