#pragma once
#include "LoggedUser.h"
#include "SqliteDataBase.h"
class LoginManager
{
private:
	IDatabase* m_database;//The database
	std::vector<LoggedUser> m_loggedUsers;//All current logged users
public:
	void signup(std::string username, std::string password, std::string email);
	void login(std::string username, std::string password);
	void logout(std::string username);
};

