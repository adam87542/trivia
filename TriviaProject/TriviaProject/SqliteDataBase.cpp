#include "SqliteDataBase.h"
#include <exception>
#include <io.h>
#define DOES_NOT_EXSIT -1

int userCallBack(void* data, int argc, char** argv, char** azColName);

void SqliteDataBase::sendSQLStatment(std::string statement, int(*callBack)(void*, int, char**, char**), std::queue<User>* userQueue)
{
	char* errMessage = nullptr;
	int res = sqlite3_exec(this->db, statement.c_str(), callBack, userQueue, &errMessage);
	if (res != SQLITE_OK)
		throw std::exception("Couldn't Send SQL Query: " + *errMessage);
}

void SqliteDataBase::openDataBase()
{
	std::string dbFileName = "Trivia.sqlite";
	int doesFileExist = _access(dbFileName.c_str(), 0);
	int res = sqlite3_open(dbFileName.c_str(), &db);

	//If the database failed to open
	if (res != SQLITE_OK)
		throw std::exception("Couldn't Open DataBase");
	if (doesFileExist == DOES_NOT_EXSIT)//If its the first time creating the database, establish the new base
		sendSQLStatment("CREATE TABLE users (username text NOT NULL,password text NOT NULL,email text NOT NULL);", nullptr, nullptr);
}

int userCallBack(void* data, int argc, char** argv, char** azColName)
{
	std::queue<User>* result = (std::queue<User>*)data;
	User user;
	for (int i = 0; i < argc; i++)
	{
		if (std::string(azColName[i]) == "username")
			user.username = atoi(argv[i]);
		else if (std::string(azColName[i]) == "password")
			user.password = atoi(argv[i]);
		else if (std::string(azColName[i]) == "email")
			user.email = atoi(argv[i]);
	}
	result->push(user);
	return 0;
}


void SqliteDataBase::clearUsers()
{
	for (int i = 0; i < users.size(); i++)
		users.pop();
}


bool SqliteDataBase::doesUserExist(std::string username)
{
	clearUsers();
	sendSQLStatment("select * from users where username = '" + username + "';", userCallBack, &users);
	return !users.empty();
}

bool SqliteDataBase::doesPasswordMatch(std::string password, std::string username)
{
	clearUsers();
	sendSQLStatment("select * from users where username = '" + username + "' and password = '" + password + "';", userCallBack, &users);
	return !users.empty();
}

void SqliteDataBase::addNewUser(std::string username, std::string password, std::string email)
{
	sendSQLStatment("insert into users values('"+ username + "','" + password + "','" + email + "');", nullptr,nullptr);
}