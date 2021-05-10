#pragma once
#include "IDatabase.h"
#include "SqliteDataBase.h"
#include "Room.h"
#include <map>
using std::vector;
using std::string;



class StatisticManager
{
public:
	StatisticManager() = default;
	static StatisticManager* get_instance();
	static void reset_instance();
	vector<std::pair<string, int>> getHighScore(Room room);
	UserStatistics getUserStatistics(string username);

private:
	static StatisticManager* m_ptr;
	static  IDatabase* m_database;
};