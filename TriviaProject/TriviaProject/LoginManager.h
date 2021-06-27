#pragma once
#include "LoggedUser.h"
#include "SqliteDataBase.h"
#include <regex>
#define MAX_PASSWORD_LENGTH 20
#define MIN_PASSWORD_LENGTH  8
#define MAX_USERNAME_LENGTH  15
#define MIN_USERNAME_LENGTH  6

class LoginManager
{
private:
	static  LoginManager* m_ptr;
	LoginManager() = default;
	~LoginManager();
	static IDatabase* m_database;//The database
	std::vector<LoggedUser> m_loggedUsers;//All current logged users
	bool CheckEmail(string email);
	bool CheckPassword(string password);
	bool CheckUserName(string username);
public:
	static LoginManager* get_instance();
	static void reset_instance();
	void signup(std::string username, std::string password, std::string email);
	void login(std::string username, std::string password);
	void logout(std::string username);
};
