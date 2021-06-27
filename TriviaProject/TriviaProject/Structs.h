#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <ctime>
#include <map>
#include "IRequestHandler.h"

class IRequestHandler;
using std::string;

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

	unsigned int totalCorrectAnswerCount;
	unsigned int  totalWrongAnswerCount;
	float averangeAnswerTime;
	int numOfPlayerGames;
};
//**************************** Question *******************************//

struct Question
{
	string question;
	string difficulty;
	string firstAnswer;
	string secondAnswer;
	string thirdAnswer;
	string fourthAnswer;
	string correctAnswer;
};
//**************************** GameData *******************************//
struct GameData
{
	string username;
	float totalAnswerTime = 0;

	Question currentQuestion;

	unsigned int correctAnswerCount = 0;

	unsigned int  wrongAnswerCount = 0;

	float averangeAnswerTime = 0;
};
struct playerResult
{
	string username;

	unsigned int correctAnswerCount = 0;

	unsigned int  wrongAnswerCount = 0;

	float averangeAnswerTime = 0;
};
//**************************** Room  ********************************// 

struct RoomData
{
	unsigned int id;
	string roomAdmin;
	string name;
	string difficulty;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timePerQuestion;
	unsigned int isGameBegan;
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
	unsigned int status;
	std::vector<RoomData> rooms;
};

struct GetPlayersInRoomResponse
{
	unsigned int status;
	std::vector<string> players;
};

struct GetHighScoreResponse
{
	unsigned int status;
	std::map<int , string> highScores;
};

struct GetPersonalStatsResponse
{
	unsigned int status;
	UserStatistics personalStatistics;
};

struct JoinRoomResponse
{
	unsigned int status;
	string roomName;
	string difficulty;
	unsigned int questionCount;
	unsigned int answerTimeOut;
	unsigned int roomId;
};

struct CreateRoomResponse
{
	unsigned int status;
	unsigned int roomId;
};

struct CloseRoomResponse
{
	unsigned int status;
};

struct StartGameResponse
{
	unsigned int status;
};

struct GetRoomStateResponse
{
	unsigned int status;
	bool hasGameBegun;
};

struct LeaveRoomResponse
{
	unsigned int status;
};

struct LeaveGameResponse
{
	unsigned int status;
};

struct GetQuestionResponse
{
	unsigned int status;
	string question;
	std::vector<string> answers;
};

struct SubmitAnswerResponse
{
	unsigned int status;
	bool isAnswerCorrect;
};

struct GetGameResultsResponse
{
	unsigned int status;
	std::list<playerResult> results;
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
	string difficulty;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeOut;
};

struct SubmitAnswerRequest
{
	float time;
	string answer;
};
