#pragma once
#include <iostream>
#include <vector>
#include "Structs.h"
#include "LoggedUser.h"

class Room
{
private:
	RoomData m_metadata; // rooms data
	std::vector<LoggedUser> m_users; // all users in room
public:
	Room() = default;
	Room(RoomData data);
	void addUser(LoggedUser user);
	void removeUser(LoggedUser user);
	// getters
	std::vector<std::string> getAllUsers();
	RoomData getData();
};