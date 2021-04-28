#include "LoginManager.h"

void LoginManager::signup(std::string username, std::string password, std::string email)
{
	if (!m_database->doesUserExist(username))
		m_database->addNewUser(username, password, email);
	else
		throw std::exception("User already exists");
}

void LoginManager::login(std::string username, std::string password)
{
	if (m_database->doesPasswordMatch(password, username))
		m_loggedUsers.push_back(LoggedUser(username));
	else
		throw std::exception("Couldn't find user or password doesn't match");
}

void LoginManager::logout(std::string username)
{
	auto currentChecked = std::find(m_loggedUsers.begin(), m_loggedUsers.end(), LoggedUser(username));
	if (currentChecked != m_loggedUsers.end())
		m_loggedUsers.erase(currentChecked);
	else
		throw std::exception("Couldn't find user to log out");
}
