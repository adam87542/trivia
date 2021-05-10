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
	vector<std::pair<string, int>> getHighScore(Room room);
	UserStatistics getUserStatistics(string username);

private:
	static  IDatabase* m_database;
};