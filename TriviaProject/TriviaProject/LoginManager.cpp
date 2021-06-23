#include "LoginManager.h"
#include "SqliteDataBase.h"
LoginManager* LoginManager::m_ptr = nullptr;
IDatabase* LoginManager::m_database = SqliteDataBase::get_instance();

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
	if (!CheckEmail(email))
		throw std::exception("Invaild email");

	else if (!CheckPassword(password))
		throw std::exception("Invalid password");

	else if (!CheckUserName(username))
		throw std::exception("Invalid username");

	else if (!m_database->doesUserExist(username))
	{
		m_database->addNewUser(username, password, email);
		m_loggedUsers.push_back(LoggedUser(username));
	}
	else
		throw std::exception("User already exists");
}

void LoginManager::login(std::string username, std::string password)
{
	if (m_database->doesPasswordMatch(password, username))
	{
		auto loggedUserItr = m_loggedUsers.begin();
		while (loggedUserItr != m_loggedUsers.end())
		{
			if (loggedUserItr->getUsername() == username)
				throw std::exception("User already logged in");
			loggedUserItr++;
		}
		m_loggedUsers.push_back(LoggedUser(username));
	}
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
			m_loggedUsers.erase(loggedUserItr);
			return;
		}
		loggedUserItr++;
	}
		throw std::exception("Couldn't find user , can't log out");
}

LoginManager::~LoginManager()
{
	SqliteDataBase::reset_instance();
	this->m_loggedUsers.clear();
}

bool LoginManager::CheckEmail(string email)
{
	const std::regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
	return std::regex_match(email, pattern);
}

bool LoginManager::CheckPassword(string password)
{
	const std::regex upperCaseExpression{ "[A-Z]+" }; //here is the very simple expression for upper_case search
	const std::regex lowerCaseExpression{ "[a-z]+" }; //for lower-case
	const std::regex numberExpression{ "[0-9]+" }; //for checking number from zero to nine
	const std::regex specialCharExpression{ "[@!?]+" }; //for the special character
	const bool hasUpperCase = std::regex_search(password, upperCaseExpression);
	const bool haslowerCase = std::regex_search(password, lowerCaseExpression);
	const bool hasNumberCase = std::regex_search(password, numberExpression);
	const bool hasSpecialChar = std::regex_search(password, specialCharExpression);
	const int IsValid = hasUpperCase + haslowerCase + hasNumberCase + hasSpecialChar;
	const bool IsValidLength = MIN_PASSWORD_LENGTH && password.length() < MAX_PASSWORD_LENGTH;
	return IsValid == 4 && IsValidLength;
}

bool LoginManager::CheckUserName(string username)
{
	bool IsValidLength = username.length() > MIN_USERNAME_LENGTH && username.length() < MAX_USERNAME_LENGTH;
	return IsValidLength;
}
