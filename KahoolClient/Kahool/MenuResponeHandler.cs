using System;
using System.Collections.Generic;
using System.Text;

namespace Kahool
{
	class MenuResponeHandler
	{

		public static bool JoinRoom(Communicator com, JoinRoomRequest request)
		{
			if (com != null)
			{
				string MsgToServer = JsonRequestSerializer.serializeRequest(request);
				string MsgFromServer = com.SendPacket(MsgToServer);
				SignUpResponse respone = JsonResponeDeserializer.deserializeSignUpRespone(MsgFromServer);
				return respone.status == Constants.Success;
			}
			return false;
		}

		public static bool CreateRoom(Communicator com, CreateRoomRequest request)
		{
			if (com != null)
			{
				string MsgToServer = JsonRequestSerializer.serializeRequest(request);
				string MsgFromServer = com.SendPacket(MsgToServer);
				LoginResponse respone = JsonResponeDeserializer.deserializeLoginRespone(MsgFromServer);
				return respone.status == Constants.Success;
			}
			return false;
		}
	}
}
