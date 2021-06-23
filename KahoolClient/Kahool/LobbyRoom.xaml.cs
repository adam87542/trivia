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
using System.Threading;

namespace Kahool
{
	/// <summary>
	/// Interaction logic for LobbyRoom.xaml
	/// </summary>
	public partial class LobbyRoom : Page
	{
		Communicator com;
		private string username;
		private bool isLeader;
		private uint roomId;
		private bool inLobby;
		MenuWindow wnd;
		private readonly object locker = new object ();

		public LobbyRoom(bool isLeader, string username, string roomId, string roomName, string timeBetweenQuestions, string difficulty, string numOfQuestions, Communicator com,MenuWindow wnd)
		{
			GetPlayersInRoomResponse room;

			this.wnd = wnd;
			this.isLeader = isLeader;
			this.username = username;
			this.roomId = uint.Parse(roomId);
			InitializeComponent();
			NumberOfQuestsionLabel.Content += numOfQuestions;
			TimeBetweenQuestionsLabel.Content += timeBetweenQuestions + " sec";
			RoomIDLabel.Content += roomId;
			RoomNameLabel.Content += roomName;
			DifficultyLabel.Content += difficulty;

			this.com = com;

			lock (this.locker)
			{
				room = LobbyResponeHandler.GetPlayersInRoom(com, this.roomId);
			}
			ListOfConnected.ItemsSource = room.playersInRoom;

			inLobby = true;
			Thread screenRefresh = new Thread(ScreenRefresh);
			screenRefresh.Start();

			if (!isLeader)//If its a guest, disable the ability to start a game, and inform them to wait
			{
				StartButton.Visibility = Visibility.Collapsed;
				CloseRoomButton.Visibility = Visibility.Collapsed;
				GuestLabel.Content = "Waiting for the leader to start";
			}
			else
				ExitButton.Visibility = Visibility.Collapsed;
		}

		public void EndRunning(object sender, RoutedEventArgs e)
		{
			lock (this.locker)
			{
				if (isLeader)
					LobbyResponeHandler.CloseRoom(this.com);
				else
					LobbyResponeHandler.LeaveRoom(this.com);
				MenuResponeHandler.LogOut(com);
			}
			System.Windows.Application.Current.Shutdown();
		}
		private void OnStartClick(object sender, RoutedEventArgs e)
		{
			inLobby = false;
		}
		private void OnExitClick(object sender, RoutedEventArgs e)
		{
			lock (this.locker)
			{
				LobbyResponeHandler.LeaveRoom(com);
			}
			inLobby = false;
			wnd.ChangeToMenu(com, username, wnd);
		}
		private void OnCloseClick(object sender, RoutedEventArgs e)
		{
			lock (this.locker)
			{
				LobbyResponeHandler.CloseRoom(this.com);
			}
			inLobby = false;
			wnd.ChangeToMenu(com, username, wnd);
		}

		public void ScreenRefresh()
		{
			while (inLobby)
			{
				GetPlayersInRoomResponse room;
				Thread.Sleep(3000);
				lock (this.locker)
				{
					room = LobbyResponeHandler.GetPlayersInRoom(com, this.roomId);
				}
				this.Dispatcher.Invoke(() =>
				{
					ListOfConnected.ItemsSource = room.playersInRoom;
				});
			}
		}
    }
}
