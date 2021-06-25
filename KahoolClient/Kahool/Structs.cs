using System;
using System.Collections.Generic;
using System.Text;

namespace Kahool
{
	//**************************** Const *********************************//
	static class Constants
	{
		public const int Success = 1;
		public const int Fail = 0;
		public const int BUFFER_START_LEN = 6;
		public const int MAX_PASSWORD_LENGTH = 20;
		public const int MIN_PASSWORD_LENGTH = 8;
		public const int MAX_USERNAME_LENGTH = 15;
		public const int MIN_USERNAME_LENGTH = 6;
		public enum requests
		{
			LOGIN_REQUEST = 20, SIGNUP_REQUEST = 30, LOGOUT_REQUEST,
			GET_ROOMS_REQUEST, GET_PLAYERS_REQUEST, JOIN_ROOM_REQUEST, CREATE_ROOM_REQUEST, GET_HIGH_SCORES_REQUEST,
			CLOSE_ROOM_REQUEST, START_GAME_REQUEST, STATE_ROOM_REQUEST, LEAVE_ROOM_REQUEST
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
	struct GetRoomStateRequest
	{
		public uint code;
	};
	struct GetPlayersInRoomRequest
	{
		public uint code;
	};

	struct CreateRoomRequest
	{
		public string roomName;
		public string difficulty;
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
	struct CloseRoomRequest
    {
		public uint code;
	};
	struct LeaveRoomRequest
	{
		public uint code;
	};

	//**************************** Responses  *********************************//
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
	struct ErrorResponse
	{
		public string message;
	};
	struct JoinRoomResponse
	{
		public uint status;
		public string roomName;
		public string difficulty;
		public uint questionCount;
		public uint answerTimeOut;
		public uint roomId;
	};
	struct CreateRoomResponse
	{
		public string roomName;
		public uint status;
		public uint roomId;
	};
	struct GetRoomStateRespone
	{
		public uint status;
		public bool IsGameBegan;
	}
	struct GetPlayersInRoomResponse
		{
		public uint status;
		public List<string> players;
         };
}
