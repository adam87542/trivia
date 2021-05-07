#pragma once
#include "IDatabase.h"
#include "Structs.h"


class SqliteDataBase : public IDatabase
{
private:
	static  SqliteDataBase* m_ptr;
	SqliteDataBase();  // no one else can create one
	~SqliteDataBase();
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

	/*
	* This fucntion gets a statment 
	* and return the sqlite3_stmt as a pointer
	* of that statment
	*/
	sqlite3_stmt* getStmt(std::string statment);
	
	/*
	* Function that creates a database if it doesn't exist
	* and opens it if it exists
	*/
	void openDataBase();

	/*
	* User callback used to retrive
	* the information after selecting it 
	* from the database
	*/
	void userCallBack(sqlite3_stmt* stmt);
public:
	static IDatabase* get_instance();
	static void reset_instance();
	 bool doesUserExist(std::string username) override;
	 bool doesPasswordMatch(std::string password, std::string username)  override;
	 void addNewUser(std::string username, std::string password, std::string email)  override;

};

