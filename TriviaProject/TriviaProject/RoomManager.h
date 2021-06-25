#pragma once
#include <iostream>
#include <algorithm>
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
	static RoomManager* getInstance();
	static void reset_instance();
	std::vector<string> getPlayersInRoom(int room_id);
	void addPlayerToRoom(int room_id , string username);
	void removePlayerFromRoom(int room_id, string username);
	Room GetRoomPlayerIsOn(string usrename);
	Room createRoom(LoggedUser user, RoomData data);
	Room GetRoomById(int roomId);
	void deleteRoom(int id);
	unsigned int getRoomState(int id);
	std::vector<RoomData> getRooms();
};