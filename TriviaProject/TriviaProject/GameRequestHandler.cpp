#include "GameRequestHandler.h"
#include "RequestHandlerFactory.h"

GameManager* GameRequestHandler::m_gameManager = GameManager::getInstance();
RoomManager* GameRequestHandler::m_roomManager = RoomManager::get_instance();
StatisticManager* GameRequestHandler::m_statisticManager = StatisticManager::get_instance();

bool GameRequestHandler::isRequestRelevant(RequestInfo info)
{
	return info.requestId == GET_Q_REQUEST  || info.requestId == info.requestId == GET_HIGH_SCORES_REQUEST || info.requestId == SUBMIT_ANSWER_REQUEST || info.requestId == GET_GAME_RESULT_REQUEST || info.requestId == LEAVE_GAME_REQUEST;
}

RequestResult GameRequestHandler::handleRequest(RequestInfo info)
{
	RequestResult myResult;
	int code = info.requestId;
	switch (code)
	{
	case GET_Q_REQUEST:
		myResult = getQuestion(info);
		break;
	case SUBMIT_ANSWER_REQUEST:
		myResult = submitAnswer(info);
		break;
	case  GET_GAME_RESULT_REQUEST:
		myResult = getGameResults(info);
		break;
	case GET_HIGH_SCORES_REQUEST:
		myResult = GetHighScores(info);
		break;
	case  LEAVE_GAME_REQUEST:
		myResult = leaveGame(info);
		break;
	default:
		myResult.newhandler = nullptr;
		myResult.response = (unsigned char*)ERROR;
		break;
	}
	return myResult;
}


RequestResult GameRequestHandler::getQuestion(RequestInfo info)
{
	RequestResult myResult;
	std::vector<Question>questions = std::vector<Question>();
	GetQuestionResponse respone;
	try
	{
		Question nextQuestion = m_gameManager->getNextQuestionOfPlayer(this->m_user->getUsername(), m_gameId , &this->m_questionCounter);
		questions = m_gameManager->getGameById(m_gameId).getQuestions();
		respone.question = nextQuestion.question;
		respone.answers.push_back(nextQuestion.firstAnswer);
		respone.answers.push_back(nextQuestion.secondAnswer);
		respone.answers.push_back(nextQuestion.thirdAnswer);
		respone.answers.push_back(nextQuestion.fourthAnswer);
	}
	catch (const std::exception e)
	{
		respone.question = e.what();
		respone.answers = std::vector<string>();
	}
	respone.status = SUCCESS_CODE;
	myResult.response = JsonResponsePacketSerializer::serializeResponse(respone);
	myResult.newhandler = RequestHandlerFactory::createGameRequestHandler(this->m_user->getUsername(),this->m_gameId , this->m_questionCounter);
	return myResult;
}

RequestResult GameRequestHandler::submitAnswer(RequestInfo info)
{
	RequestResult myResult;
	SubmitAnswerResponse respone;
	SubmitAnswerRequest request = JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(info.buffer);
	std::vector<Question>questions = m_gameManager->getGameById(m_gameId).getQuestions();
	try
	{
		respone.isAnswerCorrect = m_gameManager->SumbitAnswerOfGame(this->m_user->getUsername(), request.answer, request.time , m_gameId);
		respone.status = SUCCESS_CODE;
	}
	catch (const std::exception e)
	{
		std::cout << e.what() << std::endl;
		respone.isAnswerCorrect = false;
		respone.status = ERR_CODE;
	}
	myResult.response = JsonResponsePacketSerializer::serializeResponse(respone);
	myResult.newhandler = RequestHandlerFactory::createGameRequestHandler(this->m_user->getUsername(), this->m_gameId, this->m_questionCounter);
	return myResult;
}

RequestResult GameRequestHandler::getGameResults(RequestInfo info)
{
	RequestResult myResult;
	GetGameResultsResponse respone;
	respone.results = m_gameManager->getGameById(m_gameId).getGameResults();
	respone.status = SUCCESS_CODE;
	m_gameManager->deleteGame(m_gameId);
	myResult.newhandler = RequestHandlerFactory::createMenuRequestHandler(this->m_user->getUsername());
	myResult.response = JsonResponsePacketSerializer::serializeResponse(respone);
	return myResult;
}

RequestResult GameRequestHandler::leaveGame(RequestInfo info)
{
	RequestResult myResult;
	LeaveGameResponse respone;
	try
	{
		this->m_gameManager->removeUserFromGame(this->m_user->getUsername(), m_gameId);
		respone.status = SUCCESS_CODE;
	}
	catch (const std::exception e)
	{
		std::cout << e.what() << std::endl;
		respone.status = ERR_CODE;
	}
	myResult.newhandler = RequestHandlerFactory::createMenuRequestHandler(this->m_user->getUsername());
	myResult.response = JsonResponsePacketSerializer::serializeResponse(respone);
	return myResult;

}

RequestResult GameRequestHandler::GetHighScores(RequestInfo info)
{
	RequestResult myResult;
	GetHighScoreResponse respone;
	try
	{
		respone.highScores = m_statisticManager->getHighScore(m_gameManager->getGameById(m_gameId));
		respone.status = SUCCESS_CODE;
		myResult.response = JsonResponsePacketSerializer::serializeResponse(respone);
	}
	catch (const std::exception e)
	{
		ErrorResponse respone;
		respone.message = e.what();
		myResult.response = JsonResponsePacketSerializer::serializeResponse(respone);
		myResult.newhandler = nullptr;
	}
	return myResult;
}

GameRequestHandler::GameRequestHandler(string username, unsigned int gameId , unsigned int questionCounter)
{
	this->m_questionCounter = questionCounter;
	this->m_gameId = gameId;
	this->m_user = new LoggedUser(username);
}
