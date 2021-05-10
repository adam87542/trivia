#include "Statistic_manager.h"

IDatabase* StatisticManager::m_database = SqliteDataBase::get_instance();
StatisticManager* StatisticManager::m_ptr = StatisticManager::get_instance();

bool sortByVal(const std::pair<string, int>& a, const std::pair<string, int>& b)
{
	return (a.second < b.second);
}


StatisticManager* StatisticManager::get_instance()
{
	if (!m_ptr)
	{
		m_ptr = new StatisticManager;
	}
	return m_ptr;
}

void StatisticManager::reset_instance()
{
	delete  m_ptr;
	m_ptr = nullptr;
}

vector<std::pair<string, int>> StatisticManager::getHighScore(Room room)
{
	UserStatistics user_statistic;
	std::map<string, int> HighScores;
	vector<string> users = room.getAllUsers();
	for (const auto user : users)
	{  
		user_statistic = getUserStatistics(user);
		float score = user_statistic.numCorrectAnswers / user_statistic.avrageAnswerTime;
		HighScores.insert(std::pair<string, int>(user, score));
	}

	vector<std::pair<string, int>> High_score_vec;
	std::map<string, int> :: iterator iter;
	for (iter = HighScores.begin(); iter != HighScores.end(); iter++)
	{
		High_score_vec.push_back(make_pair(iter->first, iter->second));
	}
	std::sort(High_score_vec.begin(), High_score_vec.end(), sortByVal);


	return High_score_vec;
}

UserStatistics StatisticManager::getUserStatistics(string username)
{
	UserStatistics user_statistic;
	user_statistic.numCorrectAnswers = m_database->getNumOfCorrectAnswer(username);
	user_statistic.avrageAnswerTime = m_database->getPlayerAverageAnswerTime(username);
	user_statistic.numOfPlayerGames = m_database->getNumOfPlayerGames(username);
	user_statistic.numTotalAnswer = m_database->getNumOfTotalAnswers(username);
	return user_statistic;
}
