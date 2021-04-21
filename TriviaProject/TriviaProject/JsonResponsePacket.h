#pragma once
#include "json.hpp"
#include "Response.h"
#include "Helper.h"

using json = nlohmann::json;
#define LENGTH_BYTES 4
#define BUFFER_START_LEN 5
#define ERR_RESPONSE 0
#define LOGIN_RESPONSE 1
#define SIGNUP_RESPONSE 2
#define PASSWORD "password"
#define EMAIL "email"
#define USERNAME "username"
#define STATUS "status"

static class JsonResponsePacketSerializer
{
public:
	static unsigned char* serializeLoginResponse(LoginResponse response);
	static unsigned char* serializeSignUpResponse(SignUpResponse response);
	static unsigned char* serializeErrorResponse(ErrorResponse response);
private:
	static unsigned char* seralizingMsg(int responseNum, string msg);
};


static class JsonRequestPacketDeserializer
{
public:
	static LoginRequest DeserializeLoginRequest(unsigned char* buffer);

	static SignupRequest DeserializeSignupRequest(unsigned char* buffer);

private:
	 static json DeseralizingMsg(unsigned char* buffer);

     static string DeseralizingRespone(int respone_code);

	 friend  JsonResponsePacketSerializer; // Now JsonResponsePacketSerializer can access DeseralizingRespone

};