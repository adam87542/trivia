using System;
using System.Collections.Generic;
using System.Text;
using Newtonsoft.Json;

namespace Kahool
{

    class JsonRequestSerializer
    {
      public static string serializeRequest(LoginRequest request)
        {
            string json = JsonConvert.SerializeObject(request, Formatting.None);
            return serializeMsg((int)Constants.requests.LOGIN_REQUEST, json);
        }
        public static string serializeRequest(CloseRoomRequest request)
        {
            string json = JsonConvert.SerializeObject(request, Formatting.None);
            return serializeMsg((int)Constants.requests.CLOSE_ROOM_REQUEST, json);
        }
        public static string  serializeRequest(SignupRequest request)
        {
            string json = JsonConvert.SerializeObject(request, Formatting.None);
            return serializeMsg((int)Constants.requests.SIGNUP_REQUEST, json);
        }
        public static string serializeRequest(LogoutRequest request)
        {
            string json = JsonConvert.SerializeObject(request , Formatting.None);
            return serializeMsg((int)Constants.requests.LOGOUT_REQUEST, json);
        }
        public static string serializeRequest(LeaveRoomRequest request)
        {
            string json = JsonConvert.SerializeObject(request, Formatting.None);
            return serializeMsg((int)Constants.requests.LEAVE_ROOM_REQUEST, json);
        }
        public static string serializeRequest(JoinRoomRequest request)
        {
            string json = JsonConvert.SerializeObject(request, Formatting.None);
            return serializeMsg((int)Constants.requests.JOIN_ROOM_REQUEST, json);

        }
        public static string serializeRequest(GetPlayersInRoomRequest request)
        {
            string json = JsonConvert.SerializeObject(request, Formatting.None);
            return serializeMsg((int)Constants.requests.GET_PLAYERS_REQUEST, json);

        }
        public static string serializeRequest(CreateRoomRequest request)
        {
            string json = JsonConvert.SerializeObject(request, Formatting.None);
            return serializeMsg((int)Constants.requests.CREATE_ROOM_REQUEST, json);
        }
        public static string GetStatisticsRequest(GetStatisticsRequest request)
        {
            string json = JsonConvert.SerializeObject(request, Formatting.None);
            return serializeMsg((int)Constants.requests.GET_HIGH_SCORES_REQUEST, json);
        }
        private static string serializeMsg(int RequestId , string msg)
        {
            string length = msg.Length.ToString().PadLeft(4, '0');
            string MsgToServer = RequestId.ToString() + length + msg;
            return MsgToServer;
        }
    }
    class JsonResponeDeserializer
    {
        public static LoginResponse deserializeLoginRespone(string Buffer)
        {
            string JsonMsg = Buffer.Substring(Constants.BUFFER_START_LEN);
            LoginResponse response = JsonConvert.DeserializeObject<LoginResponse>(JsonMsg);
            return response;
        }
        public static ErrorResponse deserializeErrorRespone(string Buffer)
        {
            string JsonMsg = Buffer.Substring(Constants.BUFFER_START_LEN);
            ErrorResponse response = JsonConvert.DeserializeObject<ErrorResponse>(JsonMsg);
            return response;
        }
        public static SignUpResponse deserializeSignUpRespone(string Buffer)
        {
           string JsonMsg = Buffer.Substring(Constants.BUFFER_START_LEN);
            SignUpResponse response = JsonConvert.DeserializeObject<SignUpResponse>(JsonMsg);
            return response;
        }
        public static GetHighScoreResponse deserializeGetStatisticsRespone(string Buffer)
        {
            string JsonMsg = Buffer.Substring(Constants.BUFFER_START_LEN);
            GetHighScoreResponse response = JsonConvert.DeserializeObject<GetHighScoreResponse>(Buffer);
            return response;
        }
        public static JoinRoomResponse deserializeJoinRoomRespone(string Buffer)
        {
            string JsonMsg = Buffer.Substring(Constants.BUFFER_START_LEN);
            JoinRoomResponse response = JsonConvert.DeserializeObject<JoinRoomResponse>(JsonMsg);
            return response;
        }
        public static GetPlayersInRoomResponse deserializeGetPlayersInRoomRespone(string Buffer)
        {
            string JsonMsg = Buffer.Substring(Constants.BUFFER_START_LEN);
            GetPlayersInRoomResponse response = JsonConvert.DeserializeObject<GetPlayersInRoomResponse>(JsonMsg);
            return response;
        }
        public static CreateRoomResponse deserializeCreateRoomResponse(string Buffer)
        {
            string JsonMsg = Buffer.Substring(Constants.BUFFER_START_LEN);
            CreateRoomResponse response = JsonConvert.DeserializeObject<CreateRoomResponse>(JsonMsg);
            return response;
        }
    }
}
