#pragma once
#include "Game.h"
#include "Room.h"


class GameManager
{
private:
	static GameManager* m_ptr;
	GameManager() = default;
	~GameManager();
	std::vector<Game*> m_Games;
public:
	GameManager getInstance();
	void resetInstance();
	void createGame(Room room);
	void deleteGame(Game* currentGame);
};
