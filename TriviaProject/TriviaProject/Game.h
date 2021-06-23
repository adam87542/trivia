#pragma once
#include "Structs.h"
#include "LoggedUser.h"
#include "SqliteDataBase.h"

class Game
{
private:
	unsigned int gameId;
	static IDatabase* m_dataBase;
	std::vector<Question> m_questions;
	std::map<LoggedUser* , GameData*> m_players;
public:
	Game(string difficulty , std::vector<string> playersInRoom , unsigned int roomId);
	GameData getPlayerMeta(string username);
	Question getNextQuestion(string username);
	void submitAnswer(string username, string answer);
	void removePlayer(string username);
	unsigned int getGameId();
};