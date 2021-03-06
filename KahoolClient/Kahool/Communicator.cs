using System;
using System.Collections.Generic;
using System.Net.Sockets;
using System.Net;
using System.Text;


namespace Kahool
{
	public class Communicator
	{
		private TcpClient client;
		private IPEndPoint serverEndPoint;
		private NetworkStream socketStream;

		public Communicator()
		{

			string ServerIp = ConfigManager.getConfigIP();
			int port = ConfigManager.getConfigPort();

			try
			{
				client = new TcpClient();
				serverEndPoint = new IPEndPoint(IPAddress.Parse(ServerIp), port);
				client.Connect(serverEndPoint);
				socketStream = client.GetStream();

			}
			catch
			{
				throw new Exception("Couldn't connect to Server");
			}
		}





		public string SendPacket(string data)
		{
			try
			{
				byte[] buffer = new ASCIIEncoding().GetBytes(data);
				socketStream.Write(buffer, 0, buffer.Length);
				socketStream.Flush();
				buffer = new byte[4096];
				int bytesRead = socketStream.Read(buffer, 0, 4096);
				string MsgFromServer = Encoding.Default.GetString(buffer);
				return MsgFromServer.Trim('\0');
			}
			catch
			{
				throw new Exception("Server Not Responding");
			}
		}
	}
}
