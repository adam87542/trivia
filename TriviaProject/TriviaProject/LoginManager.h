#pragma once
#include "LoggedUser.h"
#include "SqliteDataBase.h"
#include <algorithm>

class LoginManager
{
private:
	static  LoginManager* m_ptr;
	LoginManager();
	~LoginManager();
	IDatabase* m_database;//The database
	std::vector<LoggedUser> m_loggedUsers;//All current logged users
public:
	static LoginManager* get_instance();
	static void reset_instance();
	void signup(std::string username, std::string password, std::string email);
	void login(std::string username, std::string password);
	void logout(std::string username);
};
