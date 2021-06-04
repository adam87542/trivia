using System;
using System.Collections.Generic;
using System.Text;

namespace Kahool
{
	//**************************** Requests *********************************//
	struct LoginRequest
	{
		string username;
		string password;
	};

	struct SignupRequest
	{
		string username;
		string password;
		string email;
	};
	struct JoinRoomRequest
	{
		uint roomId;
	};

	struct CreateRoomRequest
	{
		string roomName;
		uint maxUsers;
		uint questionCount;
		uint answerTimeOut;
	};
	struct LogoutRequest
	{
		uint code;
	};
	struct GetStatisticsRequest
    {
		uint code;
    };

	//**************************** Responses  *********************************//
	struct ResponeInfo
	{
		uint ResponetId;
		List<Byte> buffer;
	};
	struct GetHighScoreResponse
	{
		uint status;
		List<string> statistics;
	};

	struct JoinRoomResponse
	{
		uint status;
	};
	struct CreateRoomResponse
	{
		uint status;
	};
	struct LogoutResponse
	{
		uint status;
	};


}
