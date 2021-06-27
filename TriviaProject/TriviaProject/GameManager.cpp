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

void GameManager::deleteGame(Game currentGame)
{
	for (std::vector<Game>::iterator iter = m_Games.begin(); iter != m_Games.end(); iter++)
	{
		if (iter->getGameId() == currentGame.getGameId())
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
