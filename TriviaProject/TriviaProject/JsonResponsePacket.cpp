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

	return seralizingMsg(LOGIN_RESPONE, msg);
}

unsigned char* JsonResponsePacketSerializer::serializeResponse(SignUpResponse response)
{
	string msg = creatingStatusResponse(response.status);

	return seralizingMsg(SIGNUP_RESPONE, msg);
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

	return seralizingMsg(LOGOUT_RESPONE, msg);
}

unsigned char* JsonResponsePacketSerializer::serializeResponse(GetRoomsResponse response)
{
	json j;
	string allRooms = "";

	for (int i = 0; i < response.rooms.size(); i++) // creating string with all rooms
	{
		if (i != response.rooms.size() - 1)
		{
			allRooms += response.rooms[i].name + COMMA;
		}
		else
		{
			allRooms += response.rooms[i].name;
		}
	}

	j[ROOMS] = allRooms;

	return seralizingMsg(GET_ROOMS_RESPONE, j.dump());
}

unsigned char* JsonResponsePacketSerializer::serializeResponse(GetPlayersInRoomResponse response)
{
	json j;

	j[PLAYERS_IN_ROOM] = getAllPlayers(response.players);

	return seralizingMsg(GET_PLAYERS_RESPONE, j.dump());
}

unsigned char* JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse response)
{
	string msg = creatingStatusResponse(response.status);

	return seralizingMsg(JOIN_ROOM_RESPONE, msg);
}

unsigned char* JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse response)
{
	string msg = creatingStatusResponse(response.status);

	return seralizingMsg(CREATE_ROOM_RESPONE, msg);
}

unsigned char* JsonResponsePacketSerializer::serializeResponse(GetHighScoreResponse response)
{
	json j;
	j[USER_STATISTICS] = response.statistics[0];
	j[HIGH_SCORES] = response.statistics[1];

	return seralizingMsg(GET_HIGH_SCORES_REQUEST, j.dump());
}

unsigned char* JsonResponsePacketSerializer::serializeResponse(CloseRoomResponse response)
{
	string msg = creatingStatusResponse(response.status);

	return seralizingMsg(CLOSE_ROOM_REQUEST, msg);
}

unsigned char* JsonResponsePacketSerializer::serializeResponse(StartGameResponse response)
{
	string msg = creatingStatusResponse(response.status);

	return seralizingMsg(START_GAME_RESPONE, msg);
}

unsigned char* JsonResponsePacketSerializer::serializeResponse(GetRoomStateResponse response)
{
	json j;
	j[STATUS] = response.status;
	j[GAME_BEGUN] = response.hasGameBegun;
	j[PLAYERS_IN_ROOM] = getAllPlayers(response.players);
	j[NUM_Q] = response.questionCount;
	j[ANSWER_TIME] = response.answerTimeOut;

	return seralizingMsg(STATE_ROOM_RESPONE, j.dump());
}

unsigned char* JsonResponsePacketSerializer::serializeResponse(LeaveRoomResponse response)
{
	string msg = creatingStatusResponse(response.status);

	return seralizingMsg(LEAVE_ROOM_RESPONE, msg);
}

unsigned char* JsonResponsePacketSerializer::seralizingMsg(int responseNum, string msg)
{
	unsigned char* buffer = new unsigned char[msg.length() + BUFFER_START_LEN + 1];

	buffer[msg.length() + BUFFER_START_LEN] = 0;

	string length = Helper::getPaddedNumber(msg.length(), LENGTH_BYTES);

	buffer[0] = responseNum + '0'; // adding code

	for (unsigned int i = 0; i < LENGTH_BYTES; i++) // adding length
		buffer[i + 1] = length[i];

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

string JsonResponsePacketSerializer::getAllPlayers(std::vector<string> players)
{
	string allPlayers = "";

	for (int i = 0; i < players.size(); i++) // creating string with all players
	{
		if (i != players.size() - 1)
		{
			allPlayers += players[i] + COMMA;
		}
		else
		{
			allPlayers += players[i];
		}
	}

	return allPlayers;
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

	request.roomId = data[ID];

	return request;
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(unsigned char* buffer)
{
	JoinRoomRequest request;
	json data = deseralizingMsg(buffer);

	request.roomId = data[ID];

	return request;
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(unsigned char* buffer)
{
	CreateRoomRequest request;
	json data = deseralizingMsg(buffer);

	request.roomName = data[NAME];
	request.maxUsers = data[MAX_USERS];
	request.questionCount = data[NUM_Q];
	request.answerTimeOut = data[ANSWER_TIME];

	return request;
}

json JsonRequestPacketDeserializer::deseralizingMsg(unsigned char* buffer)
{
	json data = json::parse((char*)buffer);
	return data;
}
