﻿using System;
using System.Collections.Generic;
using System.Text;

namespace Kahool
{
    class LobbyResponeHandler
    {
        public static GetPlayersInRoomResponse GetPlayersInRoom(Communicator com)
        {
            GetPlayersInRoomRequest getPlayersInRoom;
            GetPlayersInRoomResponse playersInRoomResponse;
            playersInRoomResponse.players = null;
            playersInRoomResponse.status = 0;
            getPlayersInRoom.code = (uint)Constants.requests.GET_PLAYERS_REQUEST;
            if (com != null)
            {
                string MsgToServer = JsonRequestSerializer.serializeRequest(getPlayersInRoom);
                string MsgFromServer = com.SendPacket(MsgToServer);
                playersInRoomResponse = JsonResponeDeserializer.deserializeGetPlayersInRoomRespone(MsgFromServer);
            }
            return playersInRoomResponse;
        }
        public static void CloseRoom(Communicator com)
        {
            CloseRoomRequest closeRoomRequest;
            closeRoomRequest.code = (uint)Constants.requests.CLOSE_ROOM_REQUEST;
            if (com != null)
            {
                string MsgToServer = JsonRequestSerializer.serializeRequest(closeRoomRequest);
                string MsgFromServer = com.SendPacket(MsgToServer);
            }
        }
        public static void LeaveRoom(Communicator com)
        {
            LeaveRoomRequest request;
            request.code = (uint)Constants.requests.LEAVE_ROOM_REQUEST;
            if (com != null)
            {
                string MsgToServer = JsonRequestSerializer.serializeRequest(request);
                string MsgFromServer = com.SendPacket(MsgToServer);
            }
        }
    }
}
