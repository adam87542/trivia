﻿using System;
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
	public partial class LobbyRoom : Page
	{
		Communicator com;
		private string username;
		private bool isLeader;
		MenuWindow wnd;
		public LobbyRoom(bool isLeader, string username, string roomId, string roomName, string timeBetweenQuestions, string difficulty, string numOfQuestions, Communicator com,MenuWindow wnd)
		{
			this.wnd = wnd;
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
			else
				ExitButton.Visibility = Visibility.Collapsed;
		}

		public void EndRunning(object sender, RoutedEventArgs e)
		{
			inLobby = false;
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

		}
		private void OnExitClick(object sender, RoutedEventArgs e)
		{
			LobbyResponeHandler.LeaveRoom(com);
			wnd.ChangeToMenu(com, username, wnd);
		}
		private void OnCloseClick(object sender, RoutedEventArgs e)
		{
			LobbyResponeHandler.CloseRoom(this.com);
			wnd.ChangeToMenu(com,username, wnd);
		}

	}
}
