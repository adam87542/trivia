#pragma once
#include "Structs.h"
#include "LoggedUser.h"

class Game
{
private:
	std::vector<Question> m_questions;
	std::map<LoggedUser, GameData> m_players;
public:
	void getQuestionForUser(User user);
	void submitAnswer();
	void removePlayer();
};