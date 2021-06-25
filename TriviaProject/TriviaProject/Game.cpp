#include "Game.h"

IDatabase* Game::m_dataBase = SqliteDataBase::get_instance();

Game::Game(unsigned  int numOfQuestions , string difficulty, std::vector<string> playersInRoom , unsigned int roomId)
{
    this->m_gameId = roomId;
    this->m_numOfQuestions = numOfQuestions;
    this->m_questionDifficulty = difficulty;
    this->m_questions = m_dataBase->getQuestions(difficulty);
    for(auto player : playersInRoom)
    {
        GameData playerData;
        playerData.username = player;
        this->m_players.push_back(playerData);
    }
}

GameData* Game::getPlayerMeta(string username)
{
    for (int i = 0; i < m_players.size(); i++)
        if (m_players[i].username == username)
            return &m_players[i];
}

Question Game::getNextQuestion(string username)
{
    GameData* data = getPlayerMeta(username);
    for (int i = 0; i < m_questions.size(); i++)
        if (data->currentQuestion.question.compare(m_questions.at(i).question) && i != m_questions.size() - 1)
            return  m_questions.at(i++);
}

bool Game::submitAnswer(string username, string answer , float time)
{
    LoggedUser* user = new LoggedUser(username);
    GameData* iter = getPlayerMeta(username);
    bool  isAnswerCorrect = m_dataBase->isAnswerCorrect(answer, iter->currentQuestion.question);
    iter->totalAnswerTime += time;
    if (isAnswerCorrect)
    {
        m_dataBase->addToCorrectAnswers(username);
        iter->correctAnswerCount++;
    }
    else
    {
        m_dataBase->addToWrongAnswers(username);
        iter->wrongAnswerCount++;
    }
    iter->currentQuestion = getNextQuestion(username);
    return isAnswerCorrect;
}

void Game::removePlayer(string username)
{
    for (auto it = m_players.begin(); it != m_players.end(); ++it)
        if (it->username == username)
        {
            this->m_players.erase(it);
        }
}

unsigned int Game::getGameId()
{
    return this->m_gameId;
}

string Game::getQuestionsDifficulty()
{
    return this->m_questionDifficulty;
}

unsigned int Game::getNumOfQuestions()
{
    return this->m_numOfQuestions;
}

std::vector<string> Game::getPlayersInGame()
{
    std::vector <string> players;
    for (auto Iter = this->m_players.begin(); Iter != this->m_players.end(); ++Iter)
    {
        players.push_back(Iter->username);
    }
    return players;
}

std::vector<GameData> Game::getGameResults()
{
    for (auto player : this->m_players)
    {
        player.averangeAnswerTime = player.totalAnswerTime / this->m_numOfQuestions;
        this->m_dataBase->addToPlayerGames(player.username);
        float avgAnsTime = (this->m_dataBase->getPlayerAverageAnswerTime(player.username) + player.averangeAnswerTime) / this->m_dataBase->getNumOfPlayerGames(player.username);
        m_dataBase->setPlayerAverageAnswerTime(player.username, avgAnsTime);
    }
    return this->m_players;
}
