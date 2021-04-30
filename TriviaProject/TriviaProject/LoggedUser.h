#pragma once
#include <iostream>

class LoggedUser
{
private: 
	std::string m_username;
public:
	std::string getUsername();
};