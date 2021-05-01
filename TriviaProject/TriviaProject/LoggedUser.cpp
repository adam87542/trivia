#include "LoggedUser.h"

LoggedUser::LoggedUser(std::string newUsername)
{
    this->username = newUsername;
}

std::string LoggedUser::getUsername()
{
    return this->username;
}
