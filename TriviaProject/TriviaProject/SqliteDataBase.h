#pragma once
#include "IDatabase.h"
#include "Structs.h"


class SqliteDataBase : public IDatabase
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

	//Clears the user queue
	void clearUsers();

public:
	 bool doesUserExist(std::string username) override;
	 bool doesPasswordMatch(std::string password, std::string username)  override;
	 void addNewUser(std::string username, std::string password, std::string email)  override;

	 /*
 * Function that creates a database if it doesn't exist
 * and opens it if it exists
 */
	 void openDataBase();
};

