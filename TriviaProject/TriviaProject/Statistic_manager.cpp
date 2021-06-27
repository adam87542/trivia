#include "Statistic_manager.h"

IDatabase* StatisticManager::m_database = SqliteDataBase::get_instance();
StatisticManager* StatisticManager::m_ptr = nullptr;

bool sortByVal(const std::pair<int , string>& a, const std::pair<int , string>& b)
{
	return (a.first < b.first);
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

std::map<int , string>  StatisticManager::getHighScore(Game game)
{
	UserStatistics user_statistic;
	std::map<int, string>  HighScores;
	std::vector<std::pair<int, string>> vecOfHighScores;
	std::list<playerResult> results = game.getGameResults();
	for (const auto result : results)
	{  
		float score =  result.correctAnswerCount / result.averangeAnswerTime;
		vecOfHighScores.push_back(std::pair<int , string>(score ,result.username));
	}
	std::sort(vecOfHighScores.begin(), vecOfHighScores.end(), sortByVal);
	for (const auto pair : vecOfHighScores)
	{
		HighScores.insert(pair);
	}
	return HighScores;
}

UserStatistics StatisticManager::getUserStatistics(string username)
{
	UserStatistics user_statistic;
	user_statistic.username = username;
	user_statistic.totalCorrectAnswerCount = m_database->getNumOfCorrectAnswer(username);
	user_statistic.averangeAnswerTime = m_database->getPlayerAverageAnswerTime(username);
	user_statistic.numOfPlayerGames = m_database->getNumOfPlayerGames(username);
	user_statistic.totalWrongAnswerCount = m_database->getNumOfWrongAnswers(username);
	return user_statistic;
}
