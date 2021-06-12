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
			response.difficulty = "";
			response.answerTimeOut = 0;
			response.maxUsers = 0;
			response.questionCount = 0;

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

			if (com != null)
			{
				string MsgToServer = JsonRequestSerializer.serializeRequest(request);
				string MsgFromServer = com.SendPacket(MsgToServer);
				response = JsonResponeDeserializer.deserializeCreateRoomResponse(MsgFromServer);
			}
			return response;
		}
	}
}
