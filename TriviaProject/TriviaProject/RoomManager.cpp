#include "RoomManager.h"


RoomManager* RoomManager::m_ptr = RoomManager::getInstance();
RoomManager* RoomManager::getInstance()
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

std::vector<string> RoomManager::getPlayersInRoom(int room_id)
{
	Room room = GetRoomById(room_id);
	return room.getAllUsers();
}

Room RoomManager::addPlayerToRoom(int room_id , string username)
{
	Room itr = GetRoomById(room_id);
	itr.addUser(LoggedUser(username));
	return itr;
}

Room RoomManager::GetRoomPlayerIsOn(string usrename)
{
	for (auto room : m_rooms)
	{
		if (std::find(room.getAllUsers().begin(), room.getAllUsers().end(), usrename) != room.getAllUsers().end())
			return room;
	}
	throw std::exception("This user isnt in a room...");
}

Room RoomManager::createRoom(LoggedUser user, RoomData data)
{
	Room room(data);
	room.addUser(user);
	this->m_rooms.push_back(room);
	return room;
}

Room RoomManager::GetRoomById(int roomId)
{
	for (auto room : this->m_rooms)
	{
		if (room.getData().id == roomId)
			return room;
	}
	throw std::exception("Room Doesn't exists");
}

void RoomManager::deleteRoom(int id)
{
	auto Iter = this->m_rooms.begin();

	while (Iter != this->m_rooms.end())
	{
		if (Iter->getData().id == id)
		{
			this->m_rooms.erase(Iter);
			break;
		}
		Iter++;
	}

}

unsigned int RoomManager::getRoomState(int id)
{
	Room itr = GetRoomById(id);
	return itr.getData().isActive;
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
