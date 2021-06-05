using System;
using System.Collections.Generic;
using System.Text;

namespace Kahool
{
	class LoginResponeHandler
	{

		public static bool CheckSignUp(Communicator com,SignupRequest request)
		{
			if (com != null)
			{
				string MsgToServer = JsonRequestSerializer.serializeRequest(request);
                string MsgFromServer = com.SendPacket(MsgToServer);
				string CleanBuffer = MsgFromServer.Trim('\0');
				SignUpResponse respone = JsonResponeDeserializer.deserializeSignUpRespone(CleanBuffer);
				return respone.status == (int)Constants.Success;
			}
			return false;
		}

		public static bool CheckLogin(Communicator com, LoginRequest request)
		{
			if (com != null)
			{
				string MsgToServer = JsonRequestSerializer.serializeRequest(request);
				string MsgFromServer = com.SendPacket(MsgToServer);
				string CleanBuffer = MsgFromServer.Trim('\0');
				LoginResponse respone = JsonResponeDeserializer.deserializeLoginRespone(CleanBuffer);
				return respone.status == (int)Constants.Success;
			}
			return false;
		}
	}
}
