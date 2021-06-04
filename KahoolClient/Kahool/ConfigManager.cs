using System;
using System.Collections.Generic;
using System.Text;

namespace Kahool
{
	class ConfigManager
	{
		private static string[] getConfigContent()
		{
			return System.IO.File.ReadAllLines("config.txt");
		}

		public static string getConfigIP()
		{
			return getConfigContent()[0].Split("-")[1];
		}

		public static string getConfigPort()
		{
			return getConfigContent()[1].Split("-")[1];
		}

		public static string getConfigEncrypt()
		{
			return getConfigContent()[2].Split("-")[1];
		}
	}
}
