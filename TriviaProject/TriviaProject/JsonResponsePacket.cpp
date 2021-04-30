#include "JsonResponsePacket.h"

//**************************** Serialize *********************************//

unsigned char* JsonResponsePacketSerializer::serializeLoginResponse(LoginResponse response)
{
	string msg = creatingResponseData(response.status);

	return seralizingMsg(LOGIN_CODE, msg);
}

unsigned char* JsonResponsePacketSerializer::serializeSignUpResponse(SignUpResponse response)
{
	string msg = creatingResponseData(response.status);

	return seralizingMsg(SIGNUP_CODE, msg);
}

unsigned char* JsonResponsePacketSerializer::serializeErrorResponse(ErrorResponse response)
{
	return seralizingMsg(ERR_RESPONSE, response.message);
}

unsigned char* JsonResponsePacketSerializer::seralizingMsg(int responseNum, string msg)
{
	unsigned char* buffer = new unsigned char[msg.length() + BUFFER_START_LEN + 1];

	buffer[msg.length() + BUFFER_START_LEN] = 0;

	string length = Helper::getPaddedNumber(msg.length(), LENGTH_BYTES);

	buffer[0] = responseNum + '0'; // adding code

	for (int i = 0; i < LENGTH_BYTES; i++) // adding length
		buffer[i + 1] = (unsigned char)length[i];

	for (int i = 0; i < msg.length(); i++) // adding data
		buffer[i + BUFFER_START_LEN] = (unsigned char)msg[i];

	return buffer;
}

string JsonResponsePacketSerializer::creatingResponseData(int respone_code)
{
	json data;
	data[STATUS] = respone_code;
	string msg = data.dump();
	return msg;
}

//**************************** Deserialize *********************************//

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(unsigned char* buffer)
{
	LoginRequest login;

	json data = deseralizingMsg(buffer);

	login.password = data[PASSWORD]; // getting password
	login.username = data[USERNAME]; //getting username

	return login;

}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(unsigned char* buffer)
{
	SignupRequest sign_up;

	json data = deseralizingMsg(buffer);

	sign_up.password = data[PASSWORD]; // getting password
	sign_up.username = data[USERNAME]; //getting username
	sign_up.email = data[EMAIL]; // getting email

	return sign_up;
}

json JsonRequestPacketDeserializer::deseralizingMsg(unsigned char* buffer)
{
	json data;
	data = json::parse((char*)buffer);
	return data;
}
