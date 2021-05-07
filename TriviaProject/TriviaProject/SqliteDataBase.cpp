#include "SqliteDataBase.h"
#include <exception>
#include <io.h>
#define DOES_NOT_EXSIT -1

SqliteDataBase* SqliteDataBase::m_ptr = nullptr;


SqliteDataBase::~SqliteDataBase()
{
	delete db;
	db = nullptr;
}
SqliteDataBase::SqliteDataBase()
{
	openDataBase();
}

void SqliteDataBase::sendSQLStatment(std::string statement, int(*callBack)(void*, int, char**, char**), std::queue<User>* userQueue)
{
	char* errMessage = nullptr;
	int res = sqlite3_exec(this->db, statement.c_str(), callBack, userQueue, &errMessage);
	if (res != SQLITE_OK)
		throw std::exception("Couldn't Send SQL Query: " + *errMessage);
}

sqlite3_stmt* SqliteDataBase::getStmt(std::string statment)
{
	sqlite3_stmt* stmt;
	sqlite3_prepare(db, statment.c_str(), statment.length(), &stmt, nullptr);
	return stmt;
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

void SqliteDataBase::userCallBack(sqlite3_stmt* stmt)
{
	int result = sqlite3_step(stmt);
	while (result != SQLITE_DONE)
	{
		User user;
		user.username = std::string((char*)sqlite3_column_text(stmt,0));
		user.password = std::string((char*)sqlite3_column_text(stmt, 1));
		user.email = std::string((char*)sqlite3_column_text(stmt, 2));
		users.push(user);
		result = sqlite3_step(stmt);
	}
}

void SqliteDataBase::clearUsers()
{
	for (int i = 0; i < users.size(); i++)
		users.pop();
}

IDatabase* SqliteDataBase::get_instance()
{
	if (!m_ptr)
		m_ptr = new SqliteDataBase;
	return m_ptr;
}

void SqliteDataBase::reset_instance()
{
	delete m_ptr;
	m_ptr = nullptr;
}

bool SqliteDataBase::doesUserExist(std::string username)
{
	clearUsers();
	
	sqlite3_stmt* stmt = getStmt("select * from users where username = ?;");
	sqlite3_bind_text(stmt, 1, username.c_str(), username.length(), nullptr);
	
	userCallBack(stmt);
	return !users.empty();
}

bool SqliteDataBase::doesPasswordMatch(std::string password, std::string username)
{
	clearUsers();
	
	sqlite3_stmt* stmt = getStmt("select * from users where username = ? and password = ?;");
	sqlite3_bind_text(stmt, 1, username.c_str(), username.length(), nullptr);
	sqlite3_bind_text(stmt, 2, password.c_str(), password.length(), nullptr);

	userCallBack(stmt);
	return !users.empty();
}

void SqliteDataBase::addNewUser(std::string username, std::string password, std::string email)
{
	sqlite3_stmt* stmt = getStmt("insert into users values(?,?,?);");
	sqlite3_bind_text(stmt, 1, username.c_str(), username.length(), nullptr);
	sqlite3_bind_text(stmt, 2, password.c_str(), password.length(), nullptr);
	sqlite3_bind_text(stmt, 3, email.c_str(), email.length(), nullptr);
	userCallBack(stmt);
}