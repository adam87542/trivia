using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Kahool.Pages
{
	/// <summary>
	/// Interaction logic for RoomLobby.xaml
	/// </summary>
	public partial class RoomLobby : Page
	{
		public RoomLobby(bool isLeader)
		{
			if (!isLeader)//If its a guest, disable the abbility to start a game, and inform them to wait
			{
				StartButton.Visibility = Visibility.Collapsed;
				GuestLabel.Content = "Waiting for the leader to start";
			}	
			InitializeComponent();
		}

		public void EndRunning(object sender, RoutedEventArgs e)
		{
			System.Windows.Application.Current.Shutdown();
		}
	}
}
