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
	GetQuestionResponse respone;
	Question nextQuestion = m_Game->getNextQuestion(this->m_user->getUsername());
	this->m_questions = m_Game->getQuestions();
	respone.question = nextQuestion.question;
	respone.answers.push_back(nextQuestion.firstAnswer);
	respone.answers.push_back(nextQuestion.secondAnswer);
	respone.answers.push_back(nextQuestion.thirdAnswer);
	respone.answers.push_back(nextQuestion.fourthAnswer);
	respone.status = SUCCESS_CODE;
	myResult.response = JsonResponsePacketSerializer::serializeResponse(respone);
	myResult.newhandler = RequestHandlerFactory::createGameRequestHandler(this->m_user->getUsername(), this->m_Game->getQuestionsDifficulty(), this->m_Game->getPlayersInGame(), this->m_Game->getGameId() , this->m_Game->getNumOfQuestions() , m_questions);
	return myResult;
}

RequestResult GameRequestHandler::submitAnswer(RequestInfo info)
{
	RequestResult myResult;
	SubmitAnswerResponse respone;
	SubmitAnswerRequest request = JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(info.buffer);
	try
	{
		respone.isAnswerCorrect = m_Game->submitAnswer(this->m_user->getUsername(), request.answer, request.time);
	}
	catch (...)
	{
		respone.isAnswerCorrect = false;
	}
	respone.status = SUCCESS_CODE;
	myResult.response = JsonResponsePacketSerializer::serializeResponse(respone);
	myResult.newhandler = RequestHandlerFactory::createGameRequestHandler(this->m_user->getUsername(), this->m_Game->getQuestionsDifficulty(), this->m_Game->getPlayersInGame(), this->m_Game->getGameId() , this->m_Game->getNumOfQuestions() , m_questions);
	return myResult;
}

RequestResult GameRequestHandler::getGameResults(RequestInfo info)
{
	RequestResult myResult;
	GetGameResultsResponse respone;
	respone.results = m_Game->getGameResults();
	respone.status = SUCCESS_CODE;
	m_gameManager->deleteGame(*m_Game);
	myResult.newhandler = RequestHandlerFactory::createMenuRequestHandler(this->m_user->getUsername());
	myResult.response = JsonResponsePacketSerializer::serializeResponse(respone);
	return myResult;
}

RequestResult GameRequestHandler::leaveGame(RequestInfo info)
{
	RequestResult myResult;
	LeaveGameResponse respone;
	this->m_Game->removePlayer(this->m_user->getUsername());
	respone.status = SUCCESS_CODE;
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
		respone.highScores = m_statisticManager->getHighScore(*this->m_Game);
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

GameRequestHandler::GameRequestHandler(string username, string difficulty, std::vector<string> playersInRoom, unsigned int roomId , unsigned int numOfQuestions , std::vector<Question> questions)
{
	this->m_questions = questions;
	this->m_Game = new Game( numOfQuestions , difficulty, playersInRoom, roomId , questions);
	this->m_user = new LoggedUser(username);
	m_gameManager->createGame(*m_Game);
}
