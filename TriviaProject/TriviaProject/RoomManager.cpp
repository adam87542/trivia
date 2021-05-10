#include "RoomManager.h"

RoomManager* RoomManager::get_instance()
{
	if (!m_ptr)
	{
		m_ptr = new  RoomManager;
	}
	return m_ptr;
}

void RoomManager::reset_instance()
{
	delete m_ptr;
	m_ptr = nullptr;
}

void RoomManager::createRoom(LoggedUser user, RoomData data)
{
	Room room(data);
	room.addUser(user);
	this->m_rooms.push_back(room);
}

void RoomManager::deleteRoom(int id)
{
	auto Iter = this->m_rooms.begin();

	while (Iter != this->m_rooms.end())
	{
		if (Iter->getData().id == id)
		{
			delete &Iter;
			this->m_rooms.erase(Iter);
			break;
		}
		Iter++;
	}
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
		allRooms.push_back(it.getData());
	}

	return allRooms;
}
