using System;
using System.Collections.Generic;
using System.Text;
using Newtonsoft.Json;

namespace Kahool
{
    enum requests
    {
        LOGIN_REQUEST = 2, SIGNUP_REQUEST = 3, LOGOUT_REQUEST,
        GET_ROOMS_REQUEST, GET_PLAYERS_REQUEST, JOIN_ROOM_REQUEST, CREATE_ROOM_REQUEST, GET_HIGH_SCORES_REQUEST,
        CLOSE_ROOM_REQUEST, START_GAME_REQUEST, STATE_ROOM_REQUEST, LEAVE_ROOM_REQUEST
    };

    enum respones
    {
        LOGIN_RESPONE = 15, SIGNUP_RESPONE = 16, LOGOUT_RESPONE,
        GET_ROOMS_RESPONE, GET_PLAYERS_RESPONE, JOIN_ROOM_RESPONE, CREATE_ROOM_RESPONE, GET_HIGH_SCORES_RESPONE,
        CLOSE_ROOM_RESPONE, START_GAME_RESPONE, STATE_ROOM_RESPONE, LEAVE_ROOM_RESPONE
    };

    class JsonRequestSerializer
    {
      public static string serializeRequest(LoginRequest request)
        {
            string json = JsonConvert.SerializeObject(request, Formatting.Indented);
            return serializeMsg((int)requests.LOGIN_REQUEST, json);
        }
         public static string  serializeRequest(SignupRequest request)
        {
            string json = JsonConvert.SerializeObject(request, Formatting.Indented);
            return serializeMsg((int)requests.SIGNUP_REQUEST, json);
        }
        public static string serializeRequest(LogoutRequest request)
        {
            string json = JsonConvert.SerializeObject(request, Formatting.Indented);
            return serializeMsg((int)requests.LOGOUT_REQUEST, json);
        }
        public static string serializeRequest(JoinRoomRequest request)
        {
            string json = JsonConvert.SerializeObject(request, Formatting.Indented);
            return serializeMsg((int)requests.JOIN_ROOM_REQUEST, json);

        }
        public static string serializeRequest(CreateRoomRequest request)
        {
            string json = JsonConvert.SerializeObject(request, Formatting.Indented);
            return serializeMsg((int)requests.CREATE_ROOM_REQUEST, json);
        }
        public static string GetStatisticsRequest(GetStatisticsRequest request)
        {
            string json = JsonConvert.SerializeObject(request, Formatting.Indented);
            return serializeMsg((int)requests.GET_HIGH_SCORES_REQUEST, json);
        }
        private static string serializeMsg(int RequestId , string msg)
        {
            string MsgToServer = RequestId + msg.Length + msg;
            return MsgToServer;
        }
    }
    class JsonResponeDeserializer
    {
        public static LoginResponse deserializeLoginRespone(string Buffer)
        {
            LoginResponse response = JsonConvert.DeserializeObject<LoginResponse>(Buffer);
            return response;
        }
        public static SignUpResponse deserializeSignUpRespone(string Buffer)
        {
            SignUpResponse response = JsonConvert.DeserializeObject<SignUpResponse>(Buffer);
            return response;
        }
        public static GetHighScoreResponse deserializeGetStatisticsRespone(string Buffer)
        {
            GetHighScoreResponse response = JsonConvert.DeserializeObject<GetHighScoreResponse>(Buffer);
            return response;
        }
        public static JoinRoomResponse deserializeJoinRoomRespone(string Buffer)
        {
            JoinRoomResponse response = JsonConvert.DeserializeObject<JoinRoomResponse>(Buffer);
            return response;
        }
        public static CreateRoomResponse deserializeCreateRoomResponse(string Buffer)
        {
            CreateRoomResponse response = JsonConvert.DeserializeObject<CreateRoomResponse>(Buffer);
            return response;
        }
    }
}
