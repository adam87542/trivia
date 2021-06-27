#include "Room.h"
#include <algorithm>

Room::Room(RoomData data)
{
	this->m_metadata = data;
}

void Room::addUser(LoggedUser user)
{
	this->m_users.push_back(user);
}

void Room::removeUser(LoggedUser user)
{
	std::vector<LoggedUser>::iterator it;

	for (it = this->m_users.begin(); it != this->m_users.end(); it++)
	{
		if (it->getUsername() == user.getUsername())
		{
			this->m_users.erase(it);
			break;
		}
	}
}
void Room::SetGame()
{
	this->m_metadata.isGameBegan = true;
}

std::vector<std::string> Room::getAllUsers()
{
	std::vector<LoggedUser>::iterator it;
	std::vector<std::string> allUsersNames;

	for (it = this->m_users.begin(); it != this->m_users.end(); it++)
	{
		allUsersNames.push_back(it->getUsername());
	}

	return allUsersNames;
}

RoomData Room::getData()
{
	return this->m_metadata;
}
