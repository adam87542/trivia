#include "RoomManager.h"


RoomManager* RoomManager::m_ptr = RoomManager::get_instance();
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

std::vector<string> RoomManager::getPlayersInRoom(int room_id)
{
	return this->m_rooms[room_id].getAllUsers();
}

void RoomManager::addPlayerToRoom(int room_id , string username)
{
	this->m_rooms[room_id].addUser(LoggedUser(username));
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
