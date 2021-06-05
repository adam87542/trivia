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
				SignUpResponse respone = JsonResponeDeserializer.deserializeSignUpRespone(MsgFromServer);
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
				LoginResponse respone = JsonResponeDeserializer.deserializeLoginRespone(MsgFromServer);
				return respone.status == (int)Constants.Success;
			}
			return false;
		}
	}
}
