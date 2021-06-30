#include "Game.h"

IDatabase* Game::m_dataBase = SqliteDataBase::get_instance();

Game::Game(unsigned int gameId, string questionDifficulty, unsigned int numOfQuestions, std::vector<Question> questions, std::vector<GameData> players)
{
    this->m_gameId = gameId;
    this->m_numOfQuestions = numOfQuestions;
    this->m_questionDifficulty = questionDifficulty;
    this->m_questions = questions;
    this->m_players = players;
}

Game::Game(Game* game)
{
    this->m_gameId = game->getGameId();
    this->m_numOfQuestions = game->getNumOfQuestions();
    this->m_questionDifficulty = game->getQuestionsDifficulty();
    this->m_questions = game->getQuestions();
    this->m_players = game->getPlayersData();
}

GameData* Game::getPlayerMeta(string username)
{
    for (int i = 0; i < m_players.size(); i++)
        if (m_players[i].username == username)
            return &m_players[i];
}

Question Game::getNextQuestion(string username , unsigned int* questionCounter)
{
    GameData* iter = getPlayerMeta(username);
    iter->currentQuestion = this->m_questions.at(++*questionCounter);
    return iter->currentQuestion;
}
std::vector<Question> Game::getQuestions()
{
   return this->m_questions;
}
bool Game::submitAnswer(string username, string answer, float time)
{
    try
    {
        GameData* iter = getPlayerMeta(username);
        string question = iter->currentQuestion.question;
        bool  isAnswerCorrect = m_dataBase->isAnswerCorrect(answer, question);
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
        return isAnswerCorrect;
    }
    catch (const std::exception e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }
}

void Game::removePlayer(string username)
{
    for (auto it = m_players.begin(); it != m_players.end(); ++it)
    {
        if (it->username == username)
        {
            this->m_players.erase(it);
            return;
        }
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

std::vector<GameData> Game::getPlayersData()
{
    return this->m_players;
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

std::list<playerResult> Game::getGameResults()
{
    playerResult result;
    std::list<playerResult> results;
    for (auto player : this->m_players)
    {
        player.averangeAnswerTime = player.totalAnswerTime / this->m_numOfQuestions;
        this->m_dataBase->addToPlayerGames(player.username);
        float avgAnsTime = (this->m_dataBase->getPlayerAverageAnswerTime(player.username) + player.averangeAnswerTime) / this->m_dataBase->getNumOfPlayerGames(player.username);
        m_dataBase->setPlayerAverageAnswerTime(player.username, avgAnsTime);
        result.averangeAnswerTime = player.averangeAnswerTime;
        result.correctAnswerCount = player.correctAnswerCount;
        result.wrongAnswerCount = player.wrongAnswerCount;
        result.username = player.username;
        results.push_back(result);
    }
    return results;
}
