#include "MenuRequestHandler.h"
#include "RequestHandlerFactory.h"
#include <random>

StatisticManager* MenuRequestHandler::m_statisticManager = StatisticManager::get_instance();
RoomManager* MenuRequestHandler::m_roomManager = RoomManager::get_instance();
LoginManager* MenuRequestHandler::m_loginManager = LoginManager::get_instance();
MenuRequestHandler::MenuRequestHandler(string username)
{
	this->m_user = new LoggedUser(username);
}

bool MenuRequestHandler::isRequestRelevant(RequestInfo info)
{
	return (info.requestId == LOGOUT_REQUEST|| info.requestId == GET_ROOMS_REQUEST  || info.requestId == JOIN_ROOM_REQUEST || info.requestId == CREATE_ROOM_REQUEST || info.requestId == GET_PERSONAL_STATISTICS);
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo info)
{
	RequestResult myResult;
	int code = info.requestId;
	switch (code)
	{
	case LOGOUT_REQUEST:
		myResult = logout(info);
		break;
	case GET_ROOMS_REQUEST:
		myResult = getRooms(info);
		break;
	case GET_PERSONAL_STATISTICS:
		myResult = getPersonalStats(info);
		break;
	case JOIN_ROOM_REQUEST:
		myResult = joinRoom(info);
		break;
	case CREATE_ROOM_REQUEST:
		myResult = createRoom(info);
		break;
	}
	return myResult;
}

RequestResult MenuRequestHandler::logout(RequestInfo info)
{
	RequestResult myResult;
	LogoutResponse response;
	response.status = SUCCESS_CODE;
	m_loginManager->logout(m_user->getUsername());
	throw std::exception("User has disconnected");
	return myResult;
}

RequestResult MenuRequestHandler::getRooms(RequestInfo info)
{
	RequestResult myResult;
	GetRoomsResponse respone;
	respone.status = SUCCESS_CODE;
	respone.rooms = m_roomManager->getRooms();
	myResult.response = JsonResponsePacketSerializer::serializeResponse(respone);
	return  myResult;
}

RequestResult MenuRequestHandler::getPersonalStats(RequestInfo info)
{
	RequestResult myResult;
	GetPersonalStatsResponse response;
	response.personalStatistics = m_statisticManager->getUserStatistics(m_user->getUsername());
	response.status = SUCCESS_CODE;
	myResult.response = JsonResponsePacketSerializer::serializeResponse(response);
	myResult.newhandler = RequestHandlerFactory::createMenuRequestHandler(this->m_user->getUsername());
	return myResult;
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo info)
{
	RequestResult myResult;
	JoinRoomResponse respone;
	JoinRoomRequest  myRequest = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(info.buffer);
	try
	{
		Room roomToJoin = m_roomManager->GetRoomById(myRequest.roomId);
		respone.roomName = roomToJoin.getData().name;
		respone.answerTimeOut = roomToJoin.getData().timePerQuestion;
		respone.difficulty = roomToJoin.getData().difficulty;
		respone.questionCount = roomToJoin.getData().numOfQuestionsInGame;
		respone.roomId = roomToJoin.getData().id;
		m_roomManager->addPlayerToRoom(roomToJoin.getData().id , m_user->getUsername());
		myResult.newhandler = RequestHandlerFactory::createRoomMemberRequestHandler(m_user->getUsername(),roomToJoin);
		respone.status = SUCCESS_CODE;
	}
	catch (std::exception e)
	{
		e.what();
		respone.status = ERR_CODE;
		myResult.newhandler = RequestHandlerFactory::createMenuRequestHandler(m_user->getUsername());
	}
	myResult.response = JsonResponsePacketSerializer::serializeResponse(respone);
	return myResult;

}

RequestResult MenuRequestHandler::createRoom(RequestInfo info)
{
	RequestResult myResult;
	CreateRoomResponse respone;
	CreateRoomRequest myRequest = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(info.buffer);
	RoomData roomData;
	// Random seed
	std::random_device rd;
	int givenId = 0;
	// Initialize Mersenne Twister pseudo-random number generator
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 100);
	do
	{
		givenId = dis(gen);

	}while(IsIdExists(givenId));
	roomData.roomAdmin = this->m_user->getUsername();
	roomData.id = givenId;
	roomData.isGameBegan = false;
	roomData.maxPlayers = myRequest.maxUsers;
	roomData.name = myRequest.roomName;
	roomData.numOfQuestionsInGame = myRequest.questionCount;
	roomData.timePerQuestion = myRequest.answerTimeOut;
	roomData.difficulty = myRequest.difficulty;
	respone.roomId = roomData.id;

	respone.status = SUCCESS_CODE;

	Room UserRoom = m_roomManager->createRoom(m_user->getUsername() , roomData);
	myResult.response = JsonResponsePacketSerializer::serializeResponse(respone);
	myResult.newhandler = RequestHandlerFactory::createRoomAdminRequestHandler(m_user->getUsername() , UserRoom);
	return myResult;
}

bool MenuRequestHandler::IsIdExists(int Id)
{
	for (Room room : m_roomManager->getRooms())
	{
		if (room.getData().id == Id)
			return true;
	}
	return false;
}