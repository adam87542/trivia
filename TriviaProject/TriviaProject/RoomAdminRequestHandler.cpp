#include "RoomAdminRequestHandler.h"
#include "RequestHandlerFactory.h"

RoomManager* RoomAdminRequestHandler::m_roomManager = RoomManager::get_instance();
GameManager* RoomAdminRequestHandler::m_gameManager = GameManager::getInstance();
IDatabase* RoomAdminRequestHandler::m_dataBase = SqliteDataBase::get_instance();
RoomAdminRequestHandler::RoomAdminRequestHandler(string username , Room UserRoom)
{
		this->m_user = new LoggedUser(username);
		this->m_room = new Room(UserRoom);

}
bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo info)
{
	return info.requestId == CLOSE_ROOM_REQUEST || info.requestId == START_GAME_REQUEST  || info.requestId == GET_PLAYERS_REQUEST;
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
	m_roomManager->setGameToBeActive(m_room->getData().id);
	RoomData roomdata = this->m_room->getData();
	myResult.response = JsonResponsePacketSerializer::serializeResponse(response);
	RoomData data = this->m_room->getData();
	std::vector<Question>questions = m_dataBase->getQuestions(data.difficulty , this->m_room->getData().numOfQuestionsInGame);
	std::vector<GameData>players = std::vector<GameData>();
	for (auto player : this->m_roomManager->GetRoomById(m_room->getData().id).getAllUsers())
	{
		GameData gameData;
		gameData.username = player;
		gameData.currentQuestion = Question();
		players.push_back(gameData);
	}
	Game newGame(data.id, data.difficulty, data.numOfQuestionsInGame, questions , players );
	this->m_gameManager->createGame(newGame);
	myResult.newhandler = RequestHandlerFactory::createGameRequestHandler(this->m_user->getUsername(), roomdata.id , NULL);
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
	catch (const std::exception e)
	{
		std::cout << e.what() << std::endl;
		respone.players = std::vector<string>();
		respone.status = ERR_CODE;
		myResult.newhandler = RequestHandlerFactory::createMenuRequestHandler(username);
	}
	myResult.response = JsonResponsePacketSerializer::serializeResponse(respone);
	return myResult;
}
