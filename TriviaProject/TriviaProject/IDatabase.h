#pragma once
#include <string>
#include <queue>
#include "sqlite3.h"
#include "Structs.h"
#include <vector>

class IDatabase
{
public:
	virtual bool doesUserExist(std::string username) = 0;
	virtual bool doesPasswordMatch(std::string password, std::string username) = 0;
	virtual void addNewUser(std::string username, std::string password, std::string email) = 0;

	virtual float getPlayerAverageAnswerTime(std::string username) = 0;
	virtual int getNumOfCorrectAnswer(std::string username) = 0;
	virtual int getNumOfTotalAnswers(std::string username) = 0;
	virtual int getNumOfPlayerGames(std::string username) = 0;
	virtual std::vector<Question> getQuestions(string difficulty) = 0;
	virtual	bool isAnswerCorrect(string answer, string question) = 0;
	virtual	void addToCorrectAnswers(string username) = 0;
	virtual	void addToPlayerGames(string username) = 0;
	virtual	void addToTotalAnswers(string username) = 0;
	virtual	void setPlayerAverageAnswerTime(string username, float averageAnswerTime) =0;
};

