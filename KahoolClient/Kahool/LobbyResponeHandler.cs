using System;
using System.Collections.Generic;
using System.Text;

namespace Kahool
{
    class LobbyResponeHandler
    {
        public static GetPlayersInRoomResponse GetPlayersInRoom(Communicator com , uint RoomId)
        {
            GetPlayersInRoomRequest getPlayersInRoom;
            GetPlayersInRoomResponse playersInRoomResponse;
            string msgFromServer = "";
            playersInRoomResponse.playersInRoom= null;
            playersInRoomResponse.status = 0;
            getPlayersInRoom.roomId = RoomId;

            if (com != null)
            {
                string msgToServer = JsonRequestSerializer.serializeRequest(getPlayersInRoom);
                try
                {
                    msgFromServer = com.SendPacket(msgToServer);
                }
                catch 
                {
                    
                }
                playersInRoomResponse = JsonResponeDeserializer.deserializeGetPlayersInRoomRespone(msgFromServer);
            }
            return playersInRoomResponse;
        }
        public static void CloseRoom(Communicator com)
        {
            CloseRoomRequest closeRoomRequest;
            closeRoomRequest.code = (uint)Constants.requests.CLOSE_ROOM_REQUEST;
            if (com != null)
            {
                string msgToServer = JsonRequestSerializer.serializeRequest(closeRoomRequest);
                try
                {
                    string msgFromServer = com.SendPacket(msgToServer);
                }
                catch
                {
                    
                }
            }
        }
        public static void LeaveRoom(Communicator com)
        {
            LeaveRoomRequest request;
            request.code = (uint)Constants.requests.LEAVE_ROOM_REQUEST;
            if (com != null)
            {
                string msgToServer = JsonRequestSerializer.serializeRequest(request);
                try
                {
                    string msgFromServer = com.SendPacket(msgToServer);
                }
                catch
                {
                    
                }
            }
        }
    }
}
