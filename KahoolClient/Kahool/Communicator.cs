﻿using System;
using System.Collections.Generic;
using System.Net.Sockets;
using System.Net;
using System.Text;


namespace Kahool
{
	class Communicator
	{
		private TcpClient client;
		private IPEndPoint serverEndPoint;
		private NetworkStream socketStream;
		public static Communicator instanse = new Communicator(); 

		private Communicator()
		{
			client = new TcpClient();
			serverEndPoint = new IPEndPoint(IPAddress.Parse(ConfigManager.getConfigIP()), ConfigManager.getConfigPort());
			client.Connect(serverEndPoint);
			socketStream = client.GetStream();
		}


		public string SendPacket(string data)
		{
			byte[] buffer = new ASCIIEncoding().GetBytes(data);
			socketStream.Write(buffer, 0, buffer.Length);
			socketStream.Flush();
			buffer = new byte[4096];
			int bytesRead = socketStream.Read(buffer, 0, 4096);
			return Encoding.Default.GetString(buffer);
		}
	}
}
