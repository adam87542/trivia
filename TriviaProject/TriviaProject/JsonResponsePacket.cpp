#include "JsonResponsePacket.h"

#define LENGTH_BYTES 4
#define BUFFER_START_LEN 5
#define ERR_RESPONSE 0
#define LOGIN_RESPONSE 1
#define SIGNUP_RESPONSE 2


//**************************** Serialize *********************************//

unsigned char* JsonResponsePacketSerializer::serializeLoginResponse(LoginResponse response)
{
	json data;
	data["status"] = response.status;
	string msg = data.dump();

	return seralizingMsg(LOGIN_RESPONSE, msg);
}

unsigned char* JsonResponsePacketSerializer::serializeSignUpResponse(SignUpResponse response)
{
	json data;
	data["status"] = response.status;
	string msg = data.dump();

	return seralizingMsg(SIGNUP_RESPONSE, msg);
}

unsigned char* JsonResponsePacketSerializer::serializeErrorResponse(ErrorResponse response)
{
	json data;
	data["status"] = response.message;
	string msg = data.dump();

	return seralizingMsg(ERR_RESPONSE, msg);
}

unsigned char* JsonResponsePacketSerializer::seralizingMsg(int responseNum, string msg)
{
	unsigned char* buffer = new unsigned char[msg.length() + BUFFER_START_LEN];

	string length = Helper::getPaddedNumber(msg.length(), LENGTH_BYTES);

	buffer[0] = responseNum;

	for (int i = 0; i < LENGTH_BYTES;)
		buffer[i++] = length[i++];

	for (int i = 0; i < msg.length(); i++)
		buffer[i + LENGTH_BYTES] = msg[i];

	return buffer;
}

//**************************** Deserialize *********************************//

LoginRequest JsonRequestPacketDeserializer::DeserializeLoginRequest(unsigned char* buffer)
{
	LoginRequest* login = new LoginRequest;

	string str_buffer((char*)buffer);
	string msg = str_buffer.substr(LENGTH_BYTES, str_buffer.length() - 1);
	json data = msg;

	login->password = data["password"];
	login->username = data["username"];
	return *login;

}

SignupRequest JsonRequestPacketDeserializer::DeserializeSignupRequest(unsigned char* buffer)
{
	SignupRequest* sign_up = new SignupRequest;

	string str_buffer((char*)buffer);
	string msg = str_buffer.substr(LENGTH_BYTES, str_buffer.length() - 1);
	json data = msg;

	sign_up->password = data["password"];
	sign_up->username = data["username"];
	sign_up->email = data["email"];

	return *sign_up;
}



json JsonRequestPacketDeserializer::DeseralizingMsg(unsigned char* buffer)
{

}