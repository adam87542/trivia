#pragma once
#include "json.hpp"
#include "Structs.h"
#include "Helper.h"
#include <iostream>

using std::string;

using json = nlohmann::json;

enum requests {LOGIN_REQUEST = 2, SIGNUP_REQUEST = 3, LOGOUT_REQUEST,
	GET_ROOMS_REQUEST, GET_PLAYERS_REQUEST, JOIN_ROOM_REQUEST, CREATE_ROOM_REQUEST, GET_HIGH_SCORES_REQUEST,
	CLOSE_ROOM_REQUEST, START_GAME_REQUEST, STATE_ROOM_REQUEST, LEAVE_ROOM_REQUEST };

enum respones { LOGIN_RESPONE = 15, SIGNUP_RESPONE = 16, LOGOUT_RESPONE,
	GET_ROOMS_RESPONE, GET_PLAYERS_RESPONE, JOIN_ROOM_RESPONE, CREATE_ROOM_RESPONE, GET_HIGH_SCORES_RESPONE,
	CLOSE_ROOM_RESPONE, START_GAME_RESPONE, STATE_ROOM_RESPONE, LEAVE_ROOM_RESPONE };
#define ERR_CODE  0
#define SUCCESS_CODE  1
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