#include "IDatabase.h"
#include <exception>
#include <io.h>

void IDatabase::sendSQLStatment(std::string statement, int(*callBack)(void*, int, char**, char**))
{
	char* errMessage = nullptr;
	int res = sqlite3_exec(this->db, statement.c_str(), callBack, nullptr, &errMessage);
	if (res != SQLITE_OK)
		throw std::exception("Couldn't Send SQL Query: " + *errMessage);
}

void IDatabase::openDataBase()
{
	std::string dbFileName = "Trivia.sqlite";
	int doesFileExist = _access(dbFileName.c_str(), 0);
	int res = sqlite3_open(dbFileName.c_str(), &db);

	//If the database failed to open
	if (res != SQLITE_OK)
		throw std::exception("Couldn't Open DataBase");
	if (!doesFileExist == 0)//If its the first time creating the database, establish the new base
		sendSQLStatment("CREATE TABLE users (username text NOT NULL,password text NOT NULL,email text NOT NULL);", nullptr);
}

bool IDatabase::doesUserExist(std::string username)
{
    return false;
}

bool IDatabase::doesPasswordMatch(std::string password, std::string username)
{
    return false;
}

void IDatabase::addNewUser(std::string username, std::string password, std::string email)
{
}
