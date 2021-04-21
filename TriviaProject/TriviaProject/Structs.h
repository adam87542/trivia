#pragma once
#include <iostream>
#include <ctime>

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

struct Requestresult
{
	unsigned char* response;
	IRequestHandler* newhandler;
};


struct User
{
	string username;
	string password;
	string email;
};