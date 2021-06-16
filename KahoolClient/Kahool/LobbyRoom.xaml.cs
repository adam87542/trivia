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

namespace Kahool
{
	/// <summary>
	/// Interaction logic for LobbyRoom.xaml
	/// </summary>
	public partial class LobbyRoom :Window
	{
		Communicator com;
		private string username;
		private bool isLeader;
		public LobbyRoom(bool isLeader, string username, string roomId, string roomName, string timeBetweenQuestions, string difficulty, string numOfQuestions, Communicator com)
		{
			this.isLeader = isLeader;
			this.username = username;
			InitializeComponent();
			NumberOfQuestsionLabel.Content += numOfQuestions;
			TimeBetweenQuestionsLabel.Content += timeBetweenQuestions + " sec";
			RoomIDLabel.Content += roomId;
			RoomNameLabel.Content += roomName;
			DifficultyLabel.Content += difficulty;

			this.com = com;
			if (!isLeader)//If its a guest, disable the ability to start a game, and inform them to wait
			{
				StartButton.Visibility = Visibility.Collapsed;
				CloseRoomButton.Visibility = Visibility.Collapsed;
				GuestLabel.Content = "Waiting for the leader to start";
			}
		}

		public void EndRunning(object sender, RoutedEventArgs e)
		{
			if (isLeader)
				LobbyResponeHandler.CloseRoom(this.com);
			else
				LobbyResponeHandler.LeaveRoom(this.com);
			System.Windows.Application.Current.Shutdown();
		}
		private void OnStartClick(object sender, RoutedEventArgs e)
		{

		}
		private void OnCloseClick(object sender, RoutedEventArgs e)
		{
			LobbyResponeHandler.CloseRoom(this.com);
			this.Close();
			MenuWindow wnd = new MenuWindow(com, username);
			wnd.ShowDialog();
		}
		private void Window_MouseDown(object sender, MouseButtonEventArgs e)
		{
			if (e.ChangedButton == MouseButton.Left)
				this.DragMove();
		}

	}
}
