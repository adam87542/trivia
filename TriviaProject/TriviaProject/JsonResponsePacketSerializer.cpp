#include "JsonResponsePacketSerializer.h"

#define LENGTH_BYTES 4
#define BUFFER_START_LEN 5
#define ERR_RESPONSE 0
#define LOGIN_RESPONSE 1
#define SIGNUP_RESPONSE 2

unsigned char* JsonResponsePacketSerializer::serializeLoginResponse(LoginResponse response)
{
	json data;
	data["status"] = response.status;
	std::string msg = data.dump();

	return seralizingMsg(LOGIN_RESPONSE, msg);
}

unsigned char* JsonResponsePacketSerializer::serializeSignUpResponse(SignUpResponse response)
{
	json data;
	data["status"] = response.status;
	std::string msg = data.dump();

	return seralizingMsg(SIGNUP_RESPONSE, msg);
}

unsigned char* JsonResponsePacketSerializer::serializeErrorResponse(ErrorResponse response)
{
	json data;
	data["status"] = response.message;
	std::string msg = data.dump();

	return seralizingMsg(ERR_RESPONSE, msg);
}

unsigned char* JsonResponsePacketSerializer::seralizingMsg(int responseNum, std::string msg)
{
	unsigned char* buffer = new unsigned char[msg.length() + BUFFER_START_LEN];

	std::string length = Helper::getPaddedNumber(msg.length(), LENGTH_BYTES);

	buffer[0] = responseNum;

	for (int i = 0; i < LENGTH_BYTES; i++)
		buffer[i + 1] = length[i];

	for (int i = 0; i < msg.length(); i++)
		buffer[i + BUFFER_START_LEN] = msg[i];

	return buffer;
}
