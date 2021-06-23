#pragma once
#include "Game.h"


class GameManager
{
private:
	static GameManager* m_ptr;
	GameManager() = default;
	~GameManager();
	std::vector<Game*> m_Games;
public:
	static GameManager* getInstance();
	static void resetInstance();
	void createGame(Game* game);
	void deleteGame(Game* currentGame);
};
