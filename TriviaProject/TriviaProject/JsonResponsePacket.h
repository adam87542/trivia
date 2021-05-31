#pragma once
#include "json.hpp"
#include "Structs.h"
#include "Helper.h"
#include <iostream>

using std::string;

using json = nlohmann::json;

enum codes {ERR_CODE = 0, SUCCESS_CODE = 1, LOGIN_CODE, SIGNUP_CODE, LOGOUT_CODE, 
	GET_ROOMS_CODE, GET_PLAYERS_CODE, JOIN_ROOM_CODE, CREATE_ROOM_CODE, GET_HIGH_SCORES,
	CLOSE_ROOM_CODE, START_GAME_CODE, STATE_ROOM_CODE, LEAVE_ROOM_CODE};

#define LENGTH_BYTES 4
#define BUFFER_START_LEN 5
#define PASSWORD "password"
#define EMAIL "email"
#define USERNAME "username"
#define ID "id"
#define NAME "name" 
#define MAX_USERS "maxUsers"
#define NUM_Q "numOfQuestions"
#define ANSWER_TIME "answerTime"
#define STATUS "status"
#define ERROR "error"
#define ROOMS "rooms"
#define GAME_BEGUN "GameBegun"
#define PLAYERS_IN_ROOM "PlayersInRoom"
#define USER_STATISTICS "UserStatistics"
#define HIGH_SCORES "HighScores"
#define COMMA ","

static class JsonResponsePacketSerializer
{
public:
	static JsonResponsePacketSerializer* get_instance();
	static void reset_instance();
	static unsigned char* serializeResponse(LoginResponse response);
	static unsigned char* serializeResponse(SignUpResponse response);
	static unsigned char* serializeResponse(ErrorResponse response);
	static unsigned char* serializeResponse(LogoutResponse response);
	static unsigned char* serializeResponse(GetRoomsResponse response);
	static unsigned char* serializeResponse(GetPlayersInRoomResponse response);
	static unsigned char* serializeResponse(JoinRoomResponse response);
	static unsigned char* serializeResponse(CreateRoomResponse response);
	static unsigned char* serializeResponse(GetHighScoreResponse response);
	static unsigned char* serializeResponse(CloseRoomResponse response);
	static unsigned char* serializeResponse(StartGameResponse response);
	static unsigned char* serializeResponse(GetRoomStateResponse response);
	static unsigned char* serializeResponse(LeaveRoomResponse response);

private:
	static JsonResponsePacketSerializer* m_ptr;
	JsonResponsePacketSerializer() = default;
	/*
	* Doing seralizing to msg we get
	* input: msg and response code
	* output: seralized msg
	*/
	static unsigned char* seralizingMsg(int responseNum, string msg);
	/*
	* Function that creating data msg with json
	* input: response code
	* output: string msg
	*/
	static string creatingStatusResponse(int respone_code);
	/*
	* Function that doing a string with all players
	* input: vector with all players.
	* output: atring with all players.
	*/
	static string getAllPlayers(std::vector<string> players);
};


static class JsonRequestPacketDeserializer
{
public:
	static JsonRequestPacketDeserializer* get_instance();
	static void reset_instance();
	static LoginRequest deserializeLoginRequest(unsigned char* buffer);
	static SignupRequest deserializeSignupRequest(unsigned char* buffer);
	static GetPlayersInRoomRequest deserializeGetPlayersRequest(unsigned char* buffer);
	static JoinRoomRequest deserializeJoinRoomRequest(unsigned char* buffer);
	static CreateRoomRequest deserializeCreateRoomRequest(unsigned char* buffer);

private:
	static  JsonRequestPacketDeserializer* m_ptr;
	JsonRequestPacketDeserializer() = default;
	/*
	* Function that deseralizing the buffer into json
	* input: char ptr 
	* output: json with data
	*/
	 static json deseralizingMsg(unsigned char* buffer);
};