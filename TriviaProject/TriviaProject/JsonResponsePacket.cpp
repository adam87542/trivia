#include "JsonResponsePacket.h"

//**************************** Serialize *********************************//

JsonResponsePacketSerializer* JsonResponsePacketSerializer::m_ptr = nullptr;
JsonRequestPacketDeserializer* JsonRequestPacketDeserializer::m_ptr = nullptr;
JsonResponsePacketSerializer* JsonResponsePacketSerializer::get_instance()
{
	if (!m_ptr)
		m_ptr = new JsonResponsePacketSerializer;
	return m_ptr;
}

void JsonResponsePacketSerializer::reset_instance()
{
	delete m_ptr;
	m_ptr = nullptr;
}

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
	return seralizingMsg(ERR_CODE, response.message);
}

unsigned char* JsonResponsePacketSerializer::seralizingMsg(int responseNum, string msg)
{
	unsigned char* buffer = new unsigned char[msg.length() + BUFFER_START_LEN + 1];

	buffer[msg.length() + BUFFER_START_LEN] = 0;

	string length = Helper::getPaddedNumber(msg.length(), LENGTH_BYTES);

	buffer[0] = responseNum + '0'; // adding code

	for (unsigned int i = 0; i < LENGTH_BYTES; i++) // adding length
		buffer[i + 1] = length[i];

	for (unsigned int i = 0; i < msg.length(); i++) // adding data
		buffer[i + BUFFER_START_LEN] = msg[i];

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

JsonRequestPacketDeserializer* JsonRequestPacketDeserializer::get_instance()
{
	if (!m_ptr)
		m_ptr = new JsonRequestPacketDeserializer;
	return m_ptr;
}

void JsonRequestPacketDeserializer::reset_instance()
{
	delete m_ptr;
	m_ptr = nullptr;
}

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
