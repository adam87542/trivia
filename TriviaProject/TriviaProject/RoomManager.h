#pragma once
#include <iostream>
#include <map>
#include <vector>
#include "Room.h"

class RoomManager
{
private:
	RoomManager() = default;
	static RoomManager* m_ptr;
	std::vector<Room> m_rooms; // all open roomes
public:
	static RoomManager* get_instance();
	static void reset_instance();
	void createRoom(LoggedUser user, RoomData data);
	void deleteRoom(int id);
	unsigned int getRoomState(int id);
	std::vector<RoomData> getRooms();
};