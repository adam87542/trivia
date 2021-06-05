using System;
using System.Collections.Generic;
using System.Text;

namespace Kahool
{
	//**************************** Const *********************************//
	static class Constants
    {
		public const int BUFFER_START_LEN = 5;
		public const int MAX_PASSWORD_LENGTH = 20;
		public const int MIN_PASSWORD_LENGTH = 8;
		public const int MAX_USERNAME_LENGTH = 15;
		public const int MIN_USERNAME_LENGTH = 6;
		public	enum requests
		{
			LOGIN_REQUEST = 2, SIGNUP_REQUEST = 3, LOGOUT_REQUEST,
			GET_ROOMS_REQUEST, GET_PLAYERS_REQUEST, JOIN_ROOM_REQUEST, CREATE_ROOM_REQUEST, GET_HIGH_SCORES_REQUEST,
			CLOSE_ROOM_REQUEST, START_GAME_REQUEST, STATE_ROOM_REQUEST, LEAVE_ROOM_REQUEST
		};

		public enum respones
		{
			LOGIN_RESPONE = 15, SIGNUP_RESPONE = 16, LOGOUT_RESPONE,
			GET_ROOMS_RESPONE, GET_PLAYERS_RESPONE, JOIN_ROOM_RESPONE, CREATE_ROOM_RESPONE, GET_HIGH_SCORES_RESPONE,
			CLOSE_ROOM_RESPONE, START_GAME_RESPONE, STATE_ROOM_RESPONE, LEAVE_ROOM_RESPONE
		};
	}

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
