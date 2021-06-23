#include "GameManager.h"

GameManager* GameManager::m_ptr = new GameManager;

GameManager::~GameManager()
{
	for (auto game : this->m_Games)
		delete game;
	this->m_Games.clear();
}

GameManager* GameManager::getInstance()
{
	return m_ptr;
}

void GameManager::resetInstance()
{
	delete m_ptr;
	m_ptr = nullptr;
}

void GameManager::createGame(Game* game)
{
	this->m_Games.push_back(game);
}

void GameManager::deleteGame(Game* currentGame)
{
	for (std::vector<Game*>::iterator it = m_Games.begin(); it != m_Games.end(); it++)
	{
		Game* game = *it;
		if (game->getGameId() == currentGame->getGameId())
		{
			delete *it;
			m_Games.erase(it);
			return;
		}
	}
}
