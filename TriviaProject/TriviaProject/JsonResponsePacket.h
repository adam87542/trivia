#pragma once
#include "json.hpp"
#include "Structs.h"
#include "Helper.h"
#include <iostream>

using std::string;

using json = nlohmann::json;
#define LENGTH_BYTES 4
#define BUFFER_START_LEN 5
#define ERR_RESPONSE 0
#define LOGIN_CODE 1
#define SIGNUP_CODE 2
#define PASSWORD "password"
#define EMAIL "email"
#define USERNAME "username"
#define STATUS "status"
#define SUCCESS 1
#define FAILED 0

static class JsonResponsePacketSerializer
{
public:
	static unsigned char* serializeLoginResponse(LoginResponse response);
	static unsigned char* serializeSignUpResponse(SignUpResponse response);
	static unsigned char* serializeErrorResponse(ErrorResponse response);
private:
	/*
	* Doing seralizing to msg we get
	* input: msg and response code
	* output: seralized msg
	*/
	static unsigned char* seralizingMsg(int responseNum, string msg);
	/*
	* Function that creating data msg with json
	* input: response code
	* output: string msg
	*/
	static string creatingResponseData(int respone_code);
};


static class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(unsigned char* buffer);

	static SignupRequest deserializeSignupRequest(unsigned char* buffer);

private:
	/*
	* Function that deseralizing the buffer into json
	* input: char ptr 
	* output: json with data
	*/
	 static json deseralizingMsg(unsigned char* buffer);
};