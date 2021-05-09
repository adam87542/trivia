#include "Statistic_manager.h"

IDatabase* StatisticManager::m_database = SqliteDataBase::get_instance();

vector<string> StatisticManager::getStatistics()
{
	return vector<string>();
}

vector<string> StatisticManager::getHighScore()
{
	return vector<string>();
}

vector<string> StatisticManager::getUserStatistics(string username)
{
	return vector<string>();
}
