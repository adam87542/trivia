#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include "IRequestHandler.h"

class IRequestHandler;
using std::string;
//**************************** Room  ********************************// 

struct RoomData
{
	unsigned int id;
	string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timePerQuestion;
	unsigned int isActive;
};
//**************************** Responses  *********************************//

struct LoginResponse
{
	unsigned int status;
};

struct  SignUpResponse
{
	unsigned int status;
};

struct  ErrorResponse
{
	string message;
};

struct LogoutResponse
{
	unsigned int status;
};

struct GetRoomsResponse
{
	//unsigned int status;
	std::vector<RoomData> rooms;
};

struct GetPlayersInRoomResponse
{
	std::vector<string> players;
};

struct GetHighScoreResponse
{
	unsigned int status;
	std::vector<string> statistics;
};

struct GetPersonalStatsResponse
{
	unsigned int status;
};

struct JoinRoomResponse
{
	unsigned int status;
};

struct CreateRoomResponse
{
	unsigned int status;
};

//**************************** Requests *********************************//

struct LoginRequest
{
	string username;
	string password;
};

struct SignupRequest
{
	string username;
	string password;
	string email;
};

struct RequestInfo
{
	int requestId;
	std::time_t recivalTime;
	unsigned char* buffer;
};

struct RequestResult
{
	unsigned char* response;
	IRequestHandler* newhandler;
};

struct GetPlayersInRoomRequest
{
	unsigned int roomId;
};

struct JoinRoomRequest
{
	unsigned int roomId;
};

struct CreateRoomRequest
{
	string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeOut;
};

//****************************  User  *******************************//
struct User
{
	string username;
	string password;
	string email;
};

struct UserStatistics
{
	string username;
	float avrageAnswerTime;
	int numCorrectAnswers;
	int numTotalAnswer;
	int numOfPlayerGames;
};

//**************************** Question *******************************//

struct Question
{
	string question;
	string difficulty;
	string firstAnswer;
	string secondAnswer;
	string thridAnswer;
	string fourthAnswer;
	string correctAnswer;
	int correctAnswerIndex;
};
