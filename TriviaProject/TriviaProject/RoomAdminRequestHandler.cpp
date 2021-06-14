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
		myResult = StartGame();
		myResult.newhandler = RequestHandlerFactory::createMenuRequestHandler(m_user->getUsername());
		break;
	case STATE_ROOM_REQUEST:
		myResult = GetRoomState(*m_room);
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
	m_roomManager->deleteRoom(m_room->getData().id);
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

RequestResult RoomAdminRequestHandler::GetRoomState(Room room)
{
	RequestResult myResult;
	GetRoomStateResponse response;
	response.status = SUCCESS_CODE;
	response.answerTimeOut = room.getData().timePerQuestion;
	response.difficulty = room.getData().difficulty;
	response.questionCount = room.getData().numOfQuestionsInGame;
	myResult.response = JsonResponsePacketSerializer::serializeResponse(response);
	return myResult;
}
