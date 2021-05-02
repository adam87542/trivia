#pragma once
#include <string>
class LoggedUser
{
private:
	std::string username;
public:
	LoggedUser(std::string newUsername);
	std::string getUsername();
};
