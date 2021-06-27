#pragma once
#include "IDatabase.h"
#include "SqliteDataBase.h"
#include "Game.h"
#include <map>
using std::string;



class StatisticManager
{
public:
	StatisticManager() = default;
	static StatisticManager* get_instance();
	static void reset_instance();
	std::map<int, string>  getHighScore(Game game);
	UserStatistics getUserStatistics(string username);

private:
	static StatisticManager* m_ptr;
	static  IDatabase* m_database;
};