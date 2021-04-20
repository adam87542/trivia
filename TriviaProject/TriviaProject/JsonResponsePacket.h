#pragma once
#include "json.hpp"
#include "Response.h"
#include "Helper.h"

using json = nlohmann::json;
using std::string;

static class JsonResponsePacketSerializer
{
public:
	static unsigned char* serializeLoginResponse(LoginResponse response);
	static unsigned char* serializeSignUpResponse(SignUpResponse response);
	static unsigned char* serializeErrorResponse(ErrorResponse response);
private:
	static unsigned char* seralizingMsg(int responseNum, string msg);
	static string DeseralizingRespone(int respone_code);
};


static class JsonRequestPacketDeserializer
{
public:
	static LoginRequest DeserializeLoginRequest(unsigned char* buffer);

	static SignupRequest DeserializeSignupRequest(unsigned char* buffer);

private:
	static json DeseralizingMsg(unsigned char* buffer);

};