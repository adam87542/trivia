using System;
using System.Collections.Generic;
using System.Text;

namespace Kahool
{
	class LoginResponeHandler
	{

		public static string CheckSignUp(Communicator com, SignupRequest request)
		{
			if (com != null)
			{
				string msgFromServer = "";
				string msgToServer = JsonRequestSerializer.serializeRequest(request);
				msgFromServer = com.SendPacket(msgToServer);
				if (msgFromServer[0].ToString() == Constants.Fail.ToString())
				{
					ErrorResponse response = JsonResponeDeserializer.deserializeErrorRespone(msgFromServer);
					return response.message;
				}
				SignUpResponse respone = JsonResponeDeserializer.deserializeSignUpRespone(msgFromServer);
				if (respone.status == Constants.Success)
					return null;
			}
			return "Not connected to the server";
		}

		public static bool CheckLogin(Communicator com, LoginRequest request)
		{
			if (com != null)
			{
				string msgFromServer = "";
				string msgToServer = JsonRequestSerializer.serializeRequest(request);
				msgFromServer = com.SendPacket(msgToServer);
				LoginResponse respone = JsonResponeDeserializer.deserializeLoginRespone(msgFromServer);
				return respone.status == Constants.Success;
			}
			return false;
		}
	}
}
