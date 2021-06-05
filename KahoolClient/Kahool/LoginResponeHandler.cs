using System;
using System.Collections.Generic;
using System.Text;

namespace Kahool
{
	class LoginResponeHandler
	{

		public static bool CheckSignUp(Communicator com, SignupRequest request)
		{
			SignUpResponse respone = JsonResponeDeserializer.deserializeSignUpRespone(com.SendPacket(JsonRequestSerializer.serializeRequest(request)));
			return respone.status == (int)respones.SIGNUP_RESPONE;
		}

		public static bool CheckLogin(Communicator com, LoginRequest request)
		{
			LoginResponse respone = JsonResponeDeserializer.deserializeLoginRespone(com.SendPacket(JsonRequestSerializer.serializeRequest(request)));
			return respone.status == (int)respones.LOGIN_RESPONE;
		}
	}
}
