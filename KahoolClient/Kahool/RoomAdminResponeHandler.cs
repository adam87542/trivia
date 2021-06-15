using System;
using System.Collections.Generic;
using System.Text;

namespace Kahool
{
    class RoomAdminResponeHandler
    {
        public static GetPlayersInRoomResponse GetPlayersInRoom(Communicator com)
        {
            GetPlayersInRoomRequest getPlayersInRoom;
            getPlayersInRoom.code = (uint)Constants.requests.GET_PLAYERS_REQUEST;
            string MsgToServer = JsonRequestSerializer.serializeRequest(getPlayersInRoom);
            string MsgFromServer = com.SendPacket(MsgToServer);
            GetPlayersInRoomResponse playersInRoomResponse = JsonResponeDeserializer.deserializeGetPlayersInRoomRespone(MsgFromServer);
            return playersInRoomResponse;
        }
    }
}
