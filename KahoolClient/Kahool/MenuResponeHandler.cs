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
			string msgFromServer = "";
			response.status = Constants.Fail;
			response.roomId = 0;
			response.roomName = null;
			response.questionCount = 0;
			response.answerTimeOut = 0;
			response.difficulty = null;
			response.status = Constants.Fail;

			if (com != null)
			{
				string msgToServer = JsonRequestSerializer.serializeRequest(request);
				try
				{
					msgFromServer = com.SendPacket(msgToServer);
				}
				catch
				{

				}
				response = JsonResponeDeserializer.deserializeJoinRoomRespone(msgFromServer);
			}
			return response;
		}

		public static CreateRoomResponse CreateRoom(Communicator com, CreateRoomRequest request)
		{
			CreateRoomResponse response;
			string msgFromServer = "";
			response.status = Constants.Fail;
			response.roomId = 0;
			response.roomName = null;
			if (com != null)
			{
				string msgToServer = JsonRequestSerializer.serializeRequest(request);
				try
				{
					msgFromServer = com.SendPacket(msgToServer);
				}
				catch
				{

				}
				response = JsonResponeDeserializer.deserializeCreateRoomResponse(msgFromServer);
			}
			return response;
		}
		public static void LogOut(Communicator com)
		{
			LogoutRequest logoutRequest;
			logoutRequest.code = (uint)Constants.requests.LOGOUT_REQUEST;
			if (com != null)
			{
				string msgToServer = JsonRequestSerializer.serializeRequest(logoutRequest);
				try
				{
					string msgFromServer = com.SendPacket(msgToServer);
				}
				catch
				{

				}
			}
		}
	}
}
