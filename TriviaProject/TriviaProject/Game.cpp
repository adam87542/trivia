#include "Game.h"

IDatabase* Game::m_dataBase = SqliteDataBase::get_instance();

Game::Game(string difficulty, std::vector<string> playersInRoom)
{
    m_questions = m_dataBase->getQuestions(difficulty);
    for(auto player : playersInRoom)
    {
        LoggedUser* user = new LoggedUser(player);
        GameData* playerdata = nullptr;
        this->m_players.insert(std::pair<LoggedUser*, GameData*>(user, playerdata));
    }
}

GameData Game::getPlayerMeta(string username)
{
    for (auto it = m_players.begin(); it != m_players.end(); ++it)
        if (it->first->getUsername() == username)
            return *it->second;
}

Question Game::getNextQuestion(string username)
{
    Question currentQuestion = getPlayerMeta(username).currentQuestion;
    for (int i = 0; i < m_questions.size(); i++)
        if (currentQuestion.question.compare(m_questions.at(i).question))
            return  m_questions.at(i + 1);
}

void Game::submitAnswer(string username, string answer)
{
    LoggedUser* user = new LoggedUser(username);
    std::map<LoggedUser*, GameData*>::iterator it = this->m_players.find(user);
    if (m_dataBase->isAnswerCorrect(answer, getPlayerMeta(username).currentQuestion.question))
    {
        m_dataBase->addToCorrectAnswers(username);
        m_dataBase->addToTotalAnswers(username);
        it->second->correctAnswerCount++;
    }
    else
         it->second->wrongAnswerCount++;
    it->second->currentQuestion = getNextQuestion(username);
}

void Game::removePlayer(string username)
{
    for (auto it = m_players.begin(); it != m_players.end(); ++it)
        if (it->first->getUsername() == username)
        {
            delete it->first;
            delete it->second;
            this->m_players.erase(it);
        }
}
