#pragma once
#include <iostream>
#include <map>
#include <vector>
#include "Room.h"

class RoomManager
{
private:
	std::map<int, Room> m_rooms; // all open roomes
public:
	void createRoom(LoggedUser user, RoomData data);
	void deleteRoom(int id);
	unsigned int getRoomState(int id);
	std::vector<RoomData> getRooms();
};