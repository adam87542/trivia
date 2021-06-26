using System;
using System.Collections.Generic;
using System.Text;

namespace Kahool
{
    class GameResponeHandler
    {
        public GetQuestionResponse getNextQuestion(Communicator com)
        {
            GetQuestionRequest request;
            GetQuestionResponse questionResponse;
            questionResponse.answers = null;
            questionResponse.question = null;
            questionResponse.status = 0;
            request.code = (uint)Constants.requests.GET_Q_REQUEST;
            if (com != null)
            {
                string msgToServer = JsonRequestSerializer.serializeRequest(request);
                string msgFromServer = com.SendPacket(msgToServer);
                questionResponse = JsonResponeDeserializer.deserializeGetNexrQuestionResponse(msgFromServer);
            }
            return questionResponse;
        }
        public SubmitAnswerResponse SubmitAnswer(SubmitAnswerRequest request , Communicator com)
        {
            SubmitAnswerResponse response;
            response.isAnswerCorrect = false;
            response.status = 0;
            if (com != null)
            {
                string msgToServer = JsonRequestSerializer.serializeRequest(request);
                string msgFromServer = com.SendPacket(msgToServer);
                response = JsonResponeDeserializer.deserializeSubmitAnswerResponse(msgFromServer);

            }
            return response;
        }
        public GetGameResultsResponse getGameResults(Communicator com)
        {
            GetGameResultsRequest request;
            GetGameResultsResponse response;
            response.results = null;
            response.status = 0;
            request.code = (uint)Constants.requests.GET_GAME_RESULT_REQUEST;
            if (com != null)
            {
                string msgToServer = JsonRequestSerializer.serializeRequest(request);
                string msgFromServer = com.SendPacket(msgToServer);
                response = JsonResponeDeserializer.deserializeGetGameResultsResponse(msgFromServer);

            }
            return response;
        }
    }
}