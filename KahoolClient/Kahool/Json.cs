﻿using System;
using System.Collections.Generic;
using System.Text;
using Newtonsoft.Json;

namespace Kahool
{

    class JsonRequestSerializer
    {
      public static string serializeRequest(LoginRequest request)
        {
            string json = JsonConvert.SerializeObject(request, Formatting.Indented);
            return serializeMsg((int)Constants.requests.LOGIN_REQUEST, json);
        }
         public static string  serializeRequest(SignupRequest request)
        {
            string json = JsonConvert.SerializeObject(request, Formatting.Indented);
            return serializeMsg((int)Constants.requests.SIGNUP_REQUEST, json);
        }
        public static string serializeRequest(LogoutRequest request)
        {
            string json = JsonConvert.SerializeObject(request, Formatting.Indented);
            return serializeMsg((int)Constants.requests.LOGOUT_REQUEST, json);
        }
        public static string serializeRequest(JoinRoomRequest request)
        {
            string json = JsonConvert.SerializeObject(request, Formatting.Indented);
            return serializeMsg((int)Constants.requests.JOIN_ROOM_REQUEST, json);

        }
        public static string serializeRequest(CreateRoomRequest request)
        {
            string json = JsonConvert.SerializeObject(request, Formatting.Indented);
            return serializeMsg((int)Constants.requests.CREATE_ROOM_REQUEST, json);
        }
        public static string GetStatisticsRequest(GetStatisticsRequest request)
        {
            string json = JsonConvert.SerializeObject(request, Formatting.Indented);
            return serializeMsg((int)Constants.requests.GET_HIGH_SCORES_REQUEST, json);
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
            string JsonMsg = Buffer.Substring(Constants.BUFFER_START_LEN);
            LoginResponse response = JsonConvert.DeserializeObject<LoginResponse>(JsonMsg);
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
        public static CreateRoomResponse deserializeCreateRoomResponse(string Buffer)
        {
            string JsonMsg = Buffer.Substring(Constants.BUFFER_START_LEN);
            CreateRoomResponse response = JsonConvert.DeserializeObject<CreateRoomResponse>(JsonMsg);
            return response;
        }
    }
}
