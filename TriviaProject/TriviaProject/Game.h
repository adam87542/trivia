#pragma once
#include "Structs.h"
#include "LoggedUser.h"
#include "SqliteDataBase.h"

class Game
{
private:
	unsigned int m_gameId;
	string m_questionDifficulty;
	unsigned  int m_numOfQuestions;
	static IDatabase* m_dataBase;
	std::vector<Question> m_questions;
	std::vector<GameData> m_players;
public:
	Game(unsigned  int numOfQuestions ,  string difficulty , std::vector<string> playersInRoom , unsigned int roomId);
	GameData* getPlayerMeta(string username);
	Question getNextQuestion(string username);
	bool submitAnswer(string username, string answer , float time);
	void removePlayer(string username);
	unsigned int getGameId();
	string getQuestionsDifficulty();
	unsigned int getNumOfQuestions();
	std::vector<string> getPlayersInGame();
	std::vector<GameData> getGameResults();

};