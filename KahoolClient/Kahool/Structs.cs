using System;
using System.Collections.Generic;
using System.Text;

namespace Kahool
{
	//**************************** Requests *********************************//
	struct LoginRequest
	{
		public string username;
		public string password;
	};

	struct SignupRequest
	{
		public string username;
		public string password;
		public string email;
		public SignupRequest(string username, string password, string email)
		{
			this.username = username;
			this.password = password;
			this.email = email;
		}
	};
	struct JoinRoomRequest
	{
		public uint roomId;
	};

	struct CreateRoomRequest
	{
		public string roomName;
		public uint maxUsers;
		public uint questionCount;
		public uint answerTimeOut;
	};
	struct LogoutRequest
	{
		public uint code;
	};
	struct GetStatisticsRequest
    {
		public uint code;
    };

	//**************************** Responses  *********************************//
	struct ResponeInfo
	{
		public uint ResponetId;
		public List<Byte> buffer;
	};
	struct LoginResponse
	{
		public uint status;
	};

	struct SignUpResponse
	{
		public uint status;
	};
	struct GetHighScoreResponse
	{
		public uint status;
		public List<string> statistics;
	};

	struct JoinRoomResponse
	{
		public uint status;
	};
	struct CreateRoomResponse
	{
		public uint status;
	};
	struct LogoutResponse
	{
		public uint status;
	};


}
