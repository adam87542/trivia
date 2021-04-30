#include "RoomManager.h"

void RoomManager::createRoom(LoggedUser user, RoomData data)
{
	Room room(data);
	room.addUser(user);
	this->m_rooms.insert(std::pair<int, Room>(data.id, room));
}

void RoomManager::deleteRoom(int id)
{
	this->m_rooms.erase(id);
}

unsigned int RoomManager::getRoomState(int id)
{
	return this->m_rooms[id].getData().isActive;
}

std::vector<RoomData> RoomManager::getRooms()
{
	std::vector<RoomData> allRooms;

	for (auto it : this->m_rooms)
	{
		allRooms.push_back(it.second.getData());
	}

	return allRooms;
}
