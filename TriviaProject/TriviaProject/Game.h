#pragma once
#include "Structs.h"
#include "LoggedUser.h"

class Game
{
private:
	std::vector<Question> m_questions;
	std::map<LoggedUser* , GameData> m_players;
public:
	Game(string difficulty , std::vector<string> playersInRoom);
	Question getNextQuestion(string username);
	void submitAnswer(string username);
	void removePlayer(string username);
};