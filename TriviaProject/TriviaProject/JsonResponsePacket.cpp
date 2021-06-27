#include "JsonResponsePacket.h"

//**************************** Serialize *********************************//

JsonResponsePacketSerializer* JsonResponsePacketSerializer::m_ptr = nullptr;
JsonRequestPacketDeserializer* JsonRequestPacketDeserializer::m_ptr = nullptr;
JsonResponsePacketSerializer* JsonResponsePacketSerializer::get_instance()
{
	if (!m_ptr)
		m_ptr = new JsonResponsePacketSerializer;
	return m_ptr;
}

void JsonResponsePacketSerializer::reset_instance()
{
	delete m_ptr;
	m_ptr = nullptr;
}

unsigned char* JsonResponsePacketSerializer::serializeResponse(LoginResponse response)
{
	string msg = creatingStatusResponse(response.status);

	return seralizingMsg(LOGIN_RESPONSE, msg);
}

unsigned char* JsonResponsePacketSerializer::serializeResponse(SignUpResponse response)
{
	string msg = creatingStatusResponse(response.status);

	return seralizingMsg(SIGNUP_RESPONSE, msg);
}

unsigned char* JsonResponsePacketSerializer::serializeResponse(ErrorResponse response)
{
	json j;
	j[ERROR] = response.message;

	return seralizingMsg(ERR_CODE, j.dump());
}

unsigned char* JsonResponsePacketSerializer::serializeResponse(LogoutResponse response)
{
	string msg = creatingStatusResponse(response.status);

	return seralizingMsg(LOGOUT_RESPONSE, msg);
}

unsigned char* JsonResponsePacketSerializer::serializeResponse(GetRoomsResponse response)
{
	json j;
	std::list<string> allRooms;

	for (auto room : response.rooms)
	{
		allRooms.push_back(room.name);
	}

	j[ROOMS] = allRooms;

	return seralizingMsg(GET_ROOMS_RESPONSE, j.dump());
}

unsigned char* JsonResponsePacketSerializer::serializeResponse(GetPlayersInRoomResponse response)
{
	json j;
	j[STATUS] = response.status;
	j[PLAYERS_IN_ROOM] = vectorToList(response.players);

	return seralizingMsg(GET_PLAYERS_RESPONSE, j.dump());
}

unsigned char* JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse response)
{
	json j;
	j[STATUS] = response.status;
	j[ROOM_ID] = response.roomId;
	j[ROOMNAME] = response.roomName;
	j[NUM_Q] = response.questionCount;
	j[ANSWER_TIME_OUT] = response.answerTimeOut;
	j[DIFFICULTY] = response.difficulty;
	return seralizingMsg(JOIN_ROOM_RESPONSE, j.dump());
}

unsigned char* JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse response)
{
	json j;
	j[STATUS] = response.status;
	j[ROOM_ID] = response.roomId;
	string msg = j.dump();

	return seralizingMsg(CREATE_ROOM_RESPONSE, msg);
}

unsigned char* JsonResponsePacketSerializer::serializeResponse(GetHighScoreResponse response)
{
	json j;
	j[HIGH_SCORES] = response.highScores;

	return seralizingMsg(GET_HIGH_SCORES_RESPONSE, j.dump());
}

unsigned char* JsonResponsePacketSerializer::serializeResponse(CloseRoomResponse response)
{
	string msg = creatingStatusResponse(response.status);

	return seralizingMsg(CLOSE_ROOM_RESPONSE, msg);
}

unsigned char* JsonResponsePacketSerializer::serializeResponse(StartGameResponse response)
{
	string msg = creatingStatusResponse(response.status);

	return seralizingMsg(START_GAME_RESPONSE, msg);
}

unsigned char* JsonResponsePacketSerializer::serializeResponse(GetRoomStateResponse response)
{
	json j;
	j[STATUS] = response.status;
	j[GAME_BEGUN] = response.hasGameBegun;

	return seralizingMsg(STATE_ROOM_RESPONSE, j.dump());
}

unsigned char* JsonResponsePacketSerializer::serializeResponse(LeaveRoomResponse response)
{
	string msg = creatingStatusResponse(response.status);

	return seralizingMsg(LEAVE_ROOM_RESPONSE, msg);
}

unsigned char* JsonResponsePacketSerializer::serializeResponse(GetGameResultsResponse response)
{
	json j;
	std::list<string> myResults;
	std::string temp = "";

	if (response.status == SUCCESS_CODE)
	{
		for (auto result : response.results)
		{
			// creating string with all info
			temp = result.username;
			temp +=	COMMA;
			temp += result.correctAnswerCount;
			temp += COMMA;
			temp += result.wrongAnswerCount;
			temp += COMMA;
			temp += result.averangeAnswerTime;

			myResults.push_back(temp);
		}
		j[RESULTS] = myResults;
	}
	else
	{
		j[RESULTS] = myResults;
	}
	j[STATUS] = response.status;

	return seralizingMsg(GET_GAME_RESULT_RESPONSE, j.dump());
}

unsigned char* JsonResponsePacketSerializer::serializeResponse(SubmitAnswerResponse response)
{
	json j;
	j[STATUS] = response.status;
	j[IS_ANSWER_CORRECT] = response.isAnswerCorrect;

	return seralizingMsg(SUBMIT_ANSWER_RESPONSE, j.dump());
}

unsigned char* JsonResponsePacketSerializer::serializeResponse(GetQuestionResponse response)
{
	json j;
	if (response.status == SUCCESS_CODE)
	{
		j[QUESTION] = response.question;
		j[ANSWERS] = response.answers;
	}
	else
	{
		j[QUESTION] = "";
		j[ANSWERS] = std::map<unsigned int, string>();

	}
	j[STATUS] = response.status;

	return seralizingMsg(GET_Q_RESPONSE, j.dump());
}

unsigned char* JsonResponsePacketSerializer::serializeResponse(LeaveGameResponse response)
{
	string msg = creatingStatusResponse(response.status);

	return seralizingMsg(LEAVE_GAME_RESPONSE, msg);
}

unsigned char* JsonResponsePacketSerializer::serializeResponse(GetPersonalStatsResponse response)
{
	json j;
	j[USERNAME] = response.personalStatistics.username;
	j[AVREGE_ANSWER_TIME] = response.personalStatistics.averangeAnswerTime;
	j[TOTAL_CORRECT_ANSWERS] = response.personalStatistics.totalCorrectAnswerCount;
	j[TOTAL_WRONG_ANSWERS] = response.personalStatistics.totalWrongAnswerCount;
	j[NUM_OF_PLAYED_GAMES] = response.personalStatistics.numOfPlayerGames;
	return seralizingMsg(GET_PERSONAL_STATISTICS, j.dump());
}

unsigned char* JsonResponsePacketSerializer::seralizingMsg(int responseNum, string msg)
{
	unsigned char* buffer = new unsigned char[msg.length() + BUFFER_START_LEN + 1];

	buffer[msg.length() + BUFFER_START_LEN] = 0;

	string length = Helper::getPaddedNumber(msg.length(), LENGTH_BYTES);

	buffer[0] = responseNum % 10 + '0'; // adding code
	buffer[1] = responseNum / 10 + '0'; // adding code

	for (unsigned int i = 0; i < LENGTH_BYTES; i++) // adding length
		buffer[i + 2] = length[i];

	for (unsigned int i = 0; i < msg.length(); i++) // adding data
		buffer[i + BUFFER_START_LEN] = msg[i];

	return buffer;
}

string JsonResponsePacketSerializer::creatingStatusResponse(int respone_code)
{
	json data;
	data[STATUS] = respone_code;
	string msg = data.dump();
	return msg;
}

std::list<string> JsonResponsePacketSerializer::vectorToList(std::vector<string> src)
{
	std::list<string> dest;
	for (auto obj : src)
	{
		dest.push_back(obj);
	}
	return dest;
}

//**************************** Deserialize *********************************//

JsonRequestPacketDeserializer* JsonRequestPacketDeserializer::get_instance()
{
	if (!m_ptr)
		m_ptr = new JsonRequestPacketDeserializer;
	return m_ptr;
}

void JsonRequestPacketDeserializer::reset_instance()
{
	delete m_ptr;
	m_ptr = nullptr;
}

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(unsigned char* buffer)
{
	LoginRequest login;
	json data = deseralizingMsg(buffer);

	login.password = data[PASSWORD]; // getting password
	login.username = data[USERNAME]; //getting username

	return login;

}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(unsigned char* buffer)
{
	SignupRequest sign_up;
	json data = deseralizingMsg(buffer);

	sign_up.password = data[PASSWORD]; // getting password
	sign_up.username = data[USERNAME]; //getting username
	sign_up.email = data[EMAIL]; // getting email

	return sign_up;
}

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersRequest(unsigned char* buffer)
{
	GetPlayersInRoomRequest request;
	json data = deseralizingMsg(buffer);

	request.roomId = data[ROOM_ID];

	return request;
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(unsigned char* buffer)
{
	JoinRoomRequest request;
	json data = deseralizingMsg(buffer);

	request.roomId = data[ROOM_ID];

	return request;
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(unsigned char* buffer)
{
	CreateRoomRequest request;
	json data = deseralizingMsg(buffer);
	request.difficulty = data[DIFFICULTY];
	request.roomName = data[ROOMNAME];
	request.maxUsers = data[MAX_USERS];
	request.questionCount = data[NUM_Q];
	request.answerTimeOut = data[ANSWER_TIME_OUT];

	return request;
}

SubmitAnswerRequest JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(unsigned char* buffer)
{
	SubmitAnswerRequest request;
	json j = deseralizingMsg(buffer);
	request.answer = j[ANSWER];
	request.time = j[TIME];

	return request;
}

json JsonRequestPacketDeserializer::deseralizingMsg(unsigned char* buffer)
{
	json data = json::parse((char*)buffer);
	string msg = data.dump();
	return data;
}