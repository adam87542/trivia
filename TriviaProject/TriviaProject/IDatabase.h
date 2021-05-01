#pragma once
#include <string>
#include <queue>
#include "sqlite3.h"

class IDatabase
{
public:
	virtual bool doesUserExist(std::string username) = 0;
	virtual bool doesPasswordMatch(std::string password, std::string username) = 0;
	virtual void addNewUser(std::string username, std::string password, std::string email) = 0;
	virtual void openDataBase() = 0;
};

