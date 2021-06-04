using System;
using System.Collections.Generic;
using System.Text;

namespace Kahool
{
	class ConfigManager
	{
		private static string[] getConfigContent()
		{
			string[] data = System.IO.File.ReadAllLines("config.txt");
			if (data.Length < 3)
				throw new Exception("Config Not Right");
			return data;
		}

		public static string getConfigIP()
		{
			string ip = getConfigContent()[0];
			if (!ip.Contains("-") && ip.Split("-").Length < 2)
				throw new Exception("Config Not Right");
			return ip.Split("-")[1];
		}

		public static int getConfigPort()
		{
			string port = getConfigContent()[1];
			if (!port.Contains("-") && port.Split("-").Length < 2 && !int.TryParse(port.Split("-")[1], out _))
				throw new Exception("Config Not Right");
			return Int32.Parse(port.Split("-")[1]);
		}

		public static string getConfigEncrypt()
		{
			string isEncrypt = getConfigContent()[2];
			if (!isEncrypt.Contains("-") && isEncrypt.Split("-").Length < 2)
				throw new Exception("Config Not Right");
			return isEncrypt.Split("-")[1];
		}
	}
}
