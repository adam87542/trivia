#pragma once
#include "json.hpp"
#include "Structs.h"
#include "Helper.h"
#include <iostream>

using std::string;

using json = nlohmann::json;

enum requests {LOGIN_REQUEST = 20, SIGNUP_REQUEST = 30, LOGOUT_REQUEST,
	GET_ROOMS_REQUEST, GET_PLAYERS_REQUEST, JOIN_ROOM_REQUEST, CREATE_ROOM_REQUEST, GET_HIGH_SCORES_REQUEST,
	CLOSE_ROOM_REQUEST, START_GAME_REQUEST, STATE_ROOM_REQUEST, LEAVE_ROOM_REQUEST };

enum responses { LOGIN_RESPONSE = 20, SIGNUP_RESPONSE = 30 , LOGOUT_RESPONSE,
	GET_ROOMS_RESPONSE, GET_PLAYERS_RESPONSE, JOIN_ROOM_RESPONSE, CREATE_ROOM_RESPONSE, GET_HIGH_SCORES_RESPONSE,
	CLOSE_ROOM_RESPONSE, START_GAME_RESPONSE, STATE_ROOM_RESPONSE, LEAVE_ROOM_RESPONSE , GET_GAME_RESULT_RESPONSE,
	SUBMIT_ANSWER_RESPONSE, GET_Q_RESPONSE, LEAVE_GAME_RESPONSE};

#define ERR_CODE  0
#define SUCCESS_CODE  1
#define LENGTH_BYTES 4
#define BUFFER_START_LEN 6
#define PASSWORD "password"
#define EMAIL "email"
#define USERNAME "username"
#define ROOM_ID "roomId"
#define ROOMNAME "roomName" 
#define MAX_USERS "maxUsers"
#define NUM_Q "questionCount"
#define DIFFICULTY "difficulty"
#define ANSWER_TIME "answerTimeOut"
#define STATUS "status"
#define ERROR "message"
#define ROOMS "rooms"
#define GAME_BEGUN "GameBegun"
#define PLAYERS_IN_ROOM "PlayersInRoom"
#define USER_STATISTICS "UserStatistics"
#define HIGH_SCORES "HighScores"
#define RESULTS "Results"
#define ANSWER_ID "AnswerId" 
#define QUESTION "Question"
#define ANSWERS "Answers"
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
	static unsigned char* serializeResponse(GetGameResultsResponse response);
	static unsigned char* serializeResponse(SubmitAnswerResponse response);
	static unsigned char* serializeResponse(GetQuestionResponse response);
	static unsigned char* serializeResponse(LeaveGameResponse response);

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
	* Function that converts vector to list
	* input: vector
	* output: list
	*/
	static std::list<string> vectorToList(std::vector<string> src);
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
	static SubmitAnswerRequest deserializeSubmitAnswerRequest(unsigned char* buffer);

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