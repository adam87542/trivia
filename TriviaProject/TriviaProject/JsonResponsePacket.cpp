#include "JsonResponsePacket.h"

#define LENGTH_BYTES 4
#define BUFFER_START_LEN 5
#define ERR_RESPONSE 0
#define LOGIN_RESPONSE 1
#define SIGNUP_RESPONSE 2
#define PASSWORD "password"
#define EMAIL "email"
#define USERNAME "username"
#define STATUS "status"

//**************************** Serialize *********************************//

unsigned char* JsonResponsePacketSerializer::serializeLoginResponse(LoginResponse response)
{
	string msg = DeseralizingRespone(response.status);

	return seralizingMsg(LOGIN_RESPONSE, msg);
}

unsigned char* JsonResponsePacketSerializer::serializeSignUpResponse(SignUpResponse response)
{
	string msg = DeseralizingRespone(response.status);

	return seralizingMsg(SIGNUP_RESPONSE, msg);
}

unsigned char* JsonResponsePacketSerializer::serializeErrorResponse(ErrorResponse response)
{
	return seralizingMsg(ERR_RESPONSE, response.message);
}

unsigned char* JsonResponsePacketSerializer::seralizingMsg(int responseNum, string msg)
{
	unsigned char* buffer = new unsigned char[msg.length() + BUFFER_START_LEN];

	string length = Helper::getPaddedNumber(msg.length(), LENGTH_BYTES);

	buffer[0] = (unsigned char)responseNum;

	for (int i = 0; i < LENGTH_BYTES; i++)
		buffer[i + 1] = length[i];

	for (int i = 0; i < msg.length(); i++)
		buffer[i + LENGTH_BYTES] = msg[i];

	return buffer;
}

//**************************** Deserialize *********************************//

LoginRequest JsonRequestPacketDeserializer::DeserializeLoginRequest(unsigned char* buffer)
{
	LoginRequest* login = new LoginRequest;

	json data = DeseralizingMsg(buffer);

	login->password = data[PASSWORD];
	login->username = data[USERNAME];
	return *login;

}

SignupRequest JsonRequestPacketDeserializer::DeserializeSignupRequest(unsigned char* buffer)
{
	SignupRequest* sign_up = new SignupRequest;

	json data = DeseralizingMsg(buffer);

	sign_up->password = data[PASSWORD];
	sign_up->username = data[USERNAME];
	sign_up->email = data[EMAIL];

	return *sign_up;
}



json JsonRequestPacketDeserializer::DeseralizingMsg(unsigned char* buffer)
{
	json* data = new json;
	string str_buffer((char*)buffer);
	string msg = str_buffer.substr(LENGTH_BYTES, str_buffer.length() - 1);
	*data = msg;
	return *data;
}

string JsonResponsePacketSerializer::DeseralizingRespone(int respone_code)
{
	json data;
	data[STATUS] = respone_code;
	string msg = data.dump();
	return msg;
}
