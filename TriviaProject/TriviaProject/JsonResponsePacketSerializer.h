#pragma once
#include "json.hpp"
#include "Response.h"
#include <iostream>
#include <vector>
#include "Helper.h"
using json = nlohmann::json;

class JsonResponsePacketSerializer
{
public:
	static unsigned char* serializeLoginResponse(LoginResponse response);
	static unsigned char* serializeSignUpResponse(SignUpResponse response);
	static unsigned char* serializeErrorResponse(ErrorResponse response);
private:
	static unsigned char* seralizingMsg(int responseNum, std::string msg);
};