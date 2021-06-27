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
	return info.requestId == CLOSE_ROOM_REQUEST || info.requestId == START_GAME_REQUEST || info.requestId == STATE_ROOM_REQUEST || info.requestId == GET_PLAYERS_REQUEST;
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
		break;
	case STATE_ROOM_REQUEST:
		myResult = GetRoomState(this->m_user->getUsername() ,m_room);
		myResult.newhandler = RequestHandlerFactory::createRoomAdminRequestHandler(m_user->getUsername() , *m_room);
		break;
	case GET_PLAYERS_REQUEST:
		myResult = getPlayersInRoom(info,  false, this->m_user->getUsername(), *m_room);
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

RequestResult RoomAdminRequestHandler::StartGame()
{
	RequestResult myResult;
	StartGameResponse response;
	response.status = SUCCESS_CODE;
	m_room->SetGame();
	myResult.response = JsonResponsePacketSerializer::serializeResponse(response);
	myResult.newhandler = RequestHandlerFactory::createGameRequestHandler(this->m_user->getUsername(), this->m_room->getData().difficulty, this->m_room->getAllUsers(), this->m_room->getData().id , this->m_room->getData().numOfQuestionsInGame);
	return myResult;
}

RequestResult RoomAdminRequestHandler::GetRoomState(string username , Room* room)
{
	RequestResult myResult;
	GetRoomStateResponse response;
	response.status = SUCCESS_CODE;
	response.hasGameBegun = room->getData().isGameBegan;
	myResult.response = JsonResponsePacketSerializer::serializeResponse(response);
	myResult.newhandler = RequestHandlerFactory::createRoomAdminRequestHandler(username, *room);
	return myResult;
}
RequestResult RoomAdminRequestHandler::getPlayersInRoom(RequestInfo info , bool isMember , string username , Room room)
{
	RequestResult myResult;
	GetPlayersInRoomResponse respone;
	GetPlayersInRoomRequest myRequest = JsonRequestPacketDeserializer::deserializeGetPlayersRequest(info.buffer);
	try
	{
		respone.players = m_roomManager->getPlayersInRoom(myRequest.roomId);
		respone.status = SUCCESS_CODE;
		if(isMember)
			myResult.newhandler = myResult.newhandler = RequestHandlerFactory::createRoomMemberRequestHandler(username, room);
		else
			myResult.newhandler = myResult.newhandler = RequestHandlerFactory::createRoomAdminRequestHandler(username, room);
	}
	catch (...)
	{
		respone.players = std::vector<string>();
		respone.status = ERR_CODE;
		myResult.newhandler = RequestHandlerFactory::createMenuRequestHandler(username);
	}
	myResult.response = JsonResponsePacketSerializer::serializeResponse(respone);
	return myResult;
}
