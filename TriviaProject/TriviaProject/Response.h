#pragma once


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