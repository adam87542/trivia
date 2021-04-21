#pragma once
#include <iostream>
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



//**************************** Info *********************************//

struct RequestInfo
{
	int RequestId;
	std::time_t  receivalTime;
	unsigned char* buffer;
};