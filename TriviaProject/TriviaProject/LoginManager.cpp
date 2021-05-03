#include "LoginManager.h"

LoginManager* LoginManager::m_ptr = nullptr;
LoginManager::LoginManager()
{
	this->m_database = new SqliteDataBase;
	this->m_database->openDataBase();
}

LoginManager* LoginManager::get_instance()
{
	if (!m_ptr)
		m_ptr = new LoginManager;
	return m_ptr;
}

void LoginManager::reset_instance()
{
	delete m_ptr;
	m_ptr = nullptr;
}

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
	auto loggedUserItr = m_loggedUsers.begin();
	while (loggedUserItr != m_loggedUsers.end())
	{
		if (loggedUserItr->getUsername() == username)
		{
			delete& loggedUserItr;
			m_loggedUsers.erase(loggedUserItr);
			return;
		}
		loggedUserItr++;
	}
		throw std::exception("Couldn't find user , can't log out");
}

LoginManager::~LoginManager()
{
	delete this->m_database;
	this->m_loggedUsers.clear();
}
