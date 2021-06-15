using System;
using System.Collections.Generic;
using System.Text;

namespace Kahool
{
	class MenuResponeHandler
	{

		public static JoinRoomResponse JoinRoom(Communicator com, JoinRoomRequest request)
		{
			JoinRoomResponse response;
			response.status = Constants.Fail;
			response.roomId = 0;
			response.roomName = null;
			response.questionCount = 0;
			response.answerTimeOut = 0;
			response.difficulty = null;
			response.status = Constants.Fail;

			if (com != null)
			{
				string MsgToServer = JsonRequestSerializer.serializeRequest(request);
				string MsgFromServer = com.SendPacket(MsgToServer);
				response = JsonResponeDeserializer.deserializeJoinRoomRespone(MsgFromServer);
			}
			return response;
		}

		public static CreateRoomResponse CreateRoom(Communicator com, CreateRoomRequest request)
		{
			CreateRoomResponse response;
			response.status = Constants.Fail;
			response.roomId = 0;
			response.roomName = null;
			if (com != null)
			{
				string MsgToServer = JsonRequestSerializer.serializeRequest(request);
				string MsgFromServer = com.SendPacket(MsgToServer);
				response = JsonResponeDeserializer.deserializeCreateRoomResponse(MsgFromServer);
			}
			return response;
		}
		public static void LogOut(Communicator com)
		{
			LogoutRequest logoutRequest;
			logoutRequest.code = (uint)Constants.requests.LOGOUT_REQUEST;
			if (com != null)
			{
				string MsgToServer = JsonRequestSerializer.serializeRequest(logoutRequest);
				string MsgFromServer = com.SendPacket(MsgToServer);
			}
		}
	}
}
