#include "Game.h"

Game::Game(string difficulty, std::vector<string> playersInRoom)
{

}

Question Game::getNextQuestion(string username)
{
    for (auto it = m_players.begin(); it != m_players.end(); ++it)
        if (it->first->getUsername() == username)
            return it->second.currentQuestion;
}

void Game::submitAnswer(string  answer)
{

}

void Game::removePlayer(string username)
{
    for (auto it = m_players.begin(); it != m_players.end(); ++it)
        if (it->first->getUsername() == username)
        {
            this->m_players.erase(it);
        }
}
