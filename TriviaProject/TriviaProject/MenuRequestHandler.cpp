#include "MenuRequestHandler.h"
#include "RequestHandlerFactory.h"

StatisticManager* MenuRequestHandler::m_statisticManager = StatisticManager::get_instance();
RoomManager* MenuRequestHandler::m_roomManager = RoomManager::get_instance();
LoginManager* MenuRequestHandler::m_loginManager = LoginManager::get_instance();
MenuRequestHandler::MenuRequestHandler(string username)
{
	this->m_user = new LoggedUser(username);
}

bool MenuRequestHandler::isRequestRelevant(RequestInfo info)
{
	return (info.requestId == LOGOUT_REQUEST|| info.requestId == GET_ROOMS_REQUEST || info.requestId == GET_PLAYERS_REQUEST || info.requestId == JOIN_ROOM_REQUEST || info.requestId == CREATE_ROOM_REQUEST || info.requestId == GET_HIGH_SCORES_REQUEST);
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
	case GET_PLAYERS_REQUEST:
		myResult = getPlayersInRoom(info);
		break;
	case GET_HIGH_SCORES_REQUEST:
		myResult = getHighScore(info);
		break;
	case JOIN_ROOM_REQUEST:
		myResult = joinRoom(info);
		break;
	case CREATE_ROOM_REQUEST:
		myResult = createRoom(info);
		break;
	default:
		myResult.newhandler = nullptr;
		myResult.response = (unsigned char*)ERROR;
		break;
	}
	return myResult;
}

RequestResult MenuRequestHandler::logout(RequestInfo info)
{
	RequestResult myResult;
	LogoutResponse response;
	response.status = SUCCESS_CODE;
	for (auto room : m_roomManager->getRooms())
	{
		if (room.roomAdmin == m_user->getUsername())
		{
			m_roomManager->deleteRoom(room.id);
		}
	}
	m_loginManager->logout(m_user->getUsername());
	myResult.response = JsonResponsePacketSerializer::serializeResponse(response);
	myResult.newhandler = nullptr;
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

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo info)
{
	RequestResult myResult;
	GetPlayersInRoomResponse respone;
	GetPlayersInRoomRequest myRequest = JsonRequestPacketDeserializer::deserializeGetPlayersRequest(info.buffer);
	respone.players = m_roomManager->getPlayersInRoom(myRequest.roomId);
	myResult.response = JsonResponsePacketSerializer::serializeResponse(respone);
	return myResult;
}

RequestResult MenuRequestHandler::getHighScore(RequestInfo info)
{
	RequestResult myResult;
	GetHighScoreResponse respone;
	Room PlayersRoom;
	try
	{
		PlayersRoom = m_roomManager->GetRoomPlayerIsOn(m_user->getUsername());
	}
	catch(...)
	{
		ErrorResponse respone;
		respone.message = ERROR;
		myResult.response = JsonResponsePacketSerializer::serializeResponse(respone);
		myResult.newhandler = nullptr;
		return myResult;
	}
	respone.status = SUCCESS_CODE;
	UserStatistics statisticsOfUser = m_statisticManager->getUserStatistics(m_user->getUsername());
	string personalStats = FromUserStatisticsToString(statisticsOfUser);
	respone.statistics[0] = personalStats;
	std::vector<std::pair<string , int>> vecOfHighScores = m_statisticManager->getHighScore(PlayersRoom);
	string HighScores = FromVecToString(vecOfHighScores);
	respone.statistics[1] = HighScores;
	myResult.response = JsonResponsePacketSerializer::serializeResponse(respone);
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
		Room userRoomToJoin = m_roomManager->addPlayerToRoom(myRequest.roomId, m_user->getUsername());
		myResult.newhandler = RequestHandlerFactory::createRoomMemberRequestHandler(m_user->getUsername(), userRoomToJoin);
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

	roomData.roomAdmin = this->m_user->getUsername();
	roomData.id = m_roomManager->getRooms().size() + 1;
	roomData.isActive = true;
	roomData.maxPlayers = myRequest.maxUsers;
	roomData.name = myRequest.roomName;
	roomData.numOfQuestionsInGame = myRequest.questionCount;
	roomData.timePerQuestion = myRequest.answerTimeOut;
	roomData.difficulty = myRequest.difficulty;

	Room UserRoom = m_roomManager->createRoom(m_user->getUsername() , roomData);
	respone.status = SUCCESS_CODE;
	respone.roomId = roomData.id;
	respone.roomName = roomData.name;
	myResult.response = JsonResponsePacketSerializer::serializeResponse(respone);
	myResult.newhandler = RequestHandlerFactory::createRoomAdminRequestHandler(m_user->getUsername() , UserRoom);
	return myResult;
}

string MenuRequestHandler::FromVecToString(std::vector<std::pair<string, int>> vec)
{
	string TheVec;
	for (auto elemnet : vec)
	{
		TheVec += elemnet.first + ':' + std::to_string(elemnet.second);
		TheVec += COMMA;
	}
	return TheVec;
}

string MenuRequestHandler::FromUserStatisticsToString(UserStatistics statistics)
{
	string ans;
	ans += std::to_string(statistics.avrageAnswerTime) + COMMA;
	ans += std::to_string(statistics.numCorrectAnswers) + COMMA;
	ans += std::to_string(statistics.numOfPlayerGames) + COMMA;
	ans += std::to_string(statistics.numTotalAnswer) + COMMA;
	ans += statistics.username;
	return ans;
}
