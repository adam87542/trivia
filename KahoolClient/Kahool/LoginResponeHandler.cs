using System;
using System.Collections.Generic;
using System.Text;

namespace Kahool
{
	class LoginResponeHandler
	{

		public static bool CheckSignUp(SignupRequest request)
		{
			SignUpResponse respone = JsonResponeDeserializer.deserializeSignUpRespone(Communicator.ComInstanse.SendPacket(JsonRequestSerializer.serializeRequest(request)));
			return respone.status == (int)Constants.respones.SIGNUP_RESPONE;
		}

		public static bool CheckLogin(LoginRequest request)
		{
			LoginResponse respone = JsonResponeDeserializer.deserializeLoginRespone(Communicator.ComInstanse.SendPacket(JsonRequestSerializer.serializeRequest(request)));
			return respone.status == (int)Constants.respones.LOGIN_RESPONE;
		}
	}
}
