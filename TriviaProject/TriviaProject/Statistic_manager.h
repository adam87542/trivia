#pragma once
#include "IDatabase.h"
#include "SqliteDataBase.h"
#include <vector>
#include <iostream>
using std::vector;
using std::string;



class StatisticManager
{
public:
	 vector<string> getStatistics();

private:
	static  IDatabase* m_database;
	vector<string> getHighScore();
	vector<string> getUserStatistics(string username);
};