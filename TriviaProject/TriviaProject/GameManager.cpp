#include "GameManager.h"

GameManager* GameManager::m_ptr = new GameManager;

GameManager* GameManager::getInstance()
{
	return m_ptr;
}

void GameManager::resetInstance()
{
	delete m_ptr;
	m_ptr = nullptr;
}

void GameManager::createGame(Game game)
{
	this->m_Games.push_back(game);
}

void GameManager::deleteGame(unsigned int gameId)
{
	for (std::vector<Game>::iterator iter = m_Games.begin(); iter != m_Games.end(); iter++)
	{
		if (iter->getGameId() == gameId)
		{
			m_Games.erase(iter);
			return;
		}
	}
}

Game GameManager::getGameById(unsigned int id)
{
	for (std::vector<Game>::iterator iter = m_Games.begin(); iter != m_Games.end(); iter++)
	{
		if (iter->getGameId() == id)
		{
			return *iter;
		}
	}
}

bool GameManager::SumbitAnswerOfGame(string username, string answer, float time , unsigned int id)
{
	for (std::vector<Game>::iterator iter = m_Games.begin(); iter != m_Games.end(); iter++)
	{
		if (iter->getGameId() == id)
		{
			return iter->submitAnswer(username, answer, time);
		}
	}
	throw std::exception("Game doesnt exsit");
}

Question GameManager::getNextQuestionOfPlayer(string username , unsigned int id , unsigned int* questionCounter)
{
	for (std::vector<Game>::iterator iter = m_Games.begin(); iter != m_Games.end(); iter++)
	{
		if (iter->getGameId() == id)
		{
			return iter->getNextQuestion(username , questionCounter);
		}
	}
	throw std::exception("Game doesnt exsit");
}

std::list<playerResult> GameManager::getGameResults(unsigned int id)
{
	for (std::vector<Game>::iterator iter = m_Games.begin(); iter != m_Games.end(); iter++)
	{
		if (iter->getGameId() == id)
		{
			return iter->getGameResults();
		}
	}
	throw std::exception("Game doesnt exsit");
}

void GameManager::removeUserFromGame(string username , unsigned int id)
{
	for (std::vector<Game>::iterator iter = m_Games.begin(); iter != m_Games.end(); iter++)
	{
		if (iter->getGameId() == id)
		{
			iter->removePlayer(username);
			return;
		}
	}
	throw std::exception("Game doesnt exsit");
}
