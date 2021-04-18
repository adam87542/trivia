#pragma once
#include <string>
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