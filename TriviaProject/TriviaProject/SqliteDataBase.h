#pragma once
#include "IDatabase.h"
#include "Structs.h"
#include <queue>

class SqliteDataBase :
    public IDatabase
{
private:
	sqlite3* db;//The database
	std::queue<User> users;//Vector to hold users

	/*
	* Function that sends the sql statment instead
	* of reapting the same lines everytime, also
	* uses the callback funtion.
	*/
	void sendSQLStatment(std::string statement, int(*callBack)(void*, int, char**, char**), std::queue<User>* userQueue);

	/*
	* Function that creates a database if it doesn't exist
	* and opens it if it exists
	*/
	void openDataBase();

	//Clears the user queue
	void clearUsers();

public:
	virtual bool doesUserExist(std::string username) = 0;
	virtual bool doesPasswordMatch(std::string password, std::string username) = 0;
	virtual void addNewUser(std::string username, std::string password, std::string email) = 0;
};

