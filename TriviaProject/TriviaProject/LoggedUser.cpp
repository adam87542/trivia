#include "LoggedUser.h"

LoggedUser::LoggedUser(std::string newUsername)
{
    username = newUsername;
}

std::string LoggedUser::getUsername()
{
    return username;
}
