#pragma once
#include "IDatabase.h"
#include "SqliteDataBase.h"
#include "RoomManager.h"
#include <vector>
#include <map>
#include <iostream>
using std::vector;
using std::string;



class StatisticManager
{
public:
	std::map<string , int> getHighScore(Room room);
	UserStatistics getUserStatistics(string username);

private:
	static  IDatabase* m_database;
};