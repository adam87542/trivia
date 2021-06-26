using System;
using System.Collections.Generic;
using System.Text;

namespace Kahool
{
	class StatisticsResponseHandler
	{

		public static StatisticsResponse GetStatisticsOfUser(Communicator com)
		{
			StatisticsResponse response;
			response.averangeAnswerTime = 0;
			response.correctAnswerCount = 0;
			response.numPlayedGames = 0;
			response.wrongAnswerCount = 0;
			response.username = "";
			StatisticsRequest request;
			request.code = Convert.ToUInt32(Constants.requests.GET_PLAYER_STATISTICS_REQUEST);
			response = JsonResponeDeserializer.deserializeGetStatisticsRespone(com.SendPacket(JsonRequestSerializer.GetStatisticsRequest(request)));
			return response;
		}
	}
}
