#pragma once
#include <iostream>
#include <ctime>
#include "IRequestHandler.h"

class IRequestHandler;
using std::string;
//**************************** Respones  *********************************//

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

//****************************  User  *******************************//
struct User
{
	string username;
	string password;
	string email;
};

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