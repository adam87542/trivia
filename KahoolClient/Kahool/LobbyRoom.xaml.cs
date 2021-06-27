using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.ComponentModel;
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
		private Communicator com;
		private string username;
		private int questionTime;
		private int numOfQuestions;
		private bool isLeader;
		private uint roomId;
		private bool inLobby;
		private MenuWindow wnd;
		private readonly object locker = new object();

		public LobbyRoom(bool isLeader, string username, string roomId, string roomName, string timeBetweenQuestions, string difficulty, string numOfQuestions, Communicator com, MenuWindow wnd)
		{
			GetPlayersInRoomResponse room;
			this.wnd = wnd;
			this.questionTime = int.Parse(timeBetweenQuestions);
			this.isLeader = isLeader;
			this.numOfQuestions = int.Parse(numOfQuestions);
			this.username = username;
			this.roomId = uint.Parse(roomId);
			InitializeComponent();
			NumberOfQuestsionLabel.Content += numOfQuestions;
			TimeBetweenQuestionsLabel.Content += timeBetweenQuestions + " sec";
			RoomIDLabel.Content += roomId;
			RoomNameLabel.Content += roomName;
			DifficultyLabel.Content += difficulty;

			this.com = com;

			try
			{
				lock (this.locker)
				{
					room = LobbyResponeHandler.GetPlayersInRoom(com, this.roomId);
				}
				ListOfConnected.ItemsSource = room.playersInRoom;
			}
			catch
			{
				wnd.ChangeToError(wnd);
			}

			inLobby = true;
			Thread screenRefresh = new Thread(ScreenRefresh);
			screenRefresh.Start();
			if (!this.isLeader)
			{
				Thread Checker = new Thread(CheckIfGameHasStarted);
				Checker.Start();
			}
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
			try
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
			catch
			{
				wnd.ChangeToError(wnd);
			}
		}
		private void OnStartClick(object sender, RoutedEventArgs e)
		{
			try
			{
				lock (this.locker)
				{
					LobbyResponeHandler.StartGame(com);
				}
				inLobby = false;
				GetQuestionResponse response = GameResponeHandler.getNextQuestion(com);
				wnd.ChangeToQuestion(this.questionTime, response.question, response.Answers, com, wnd, 1, this.numOfQuestions);

			}
			catch
			{
				wnd.ChangeToError(wnd);
			}
		}
		private void OnExitClick(object sender, RoutedEventArgs e)
		{
			try
			{
				lock (this.locker)
				{
					LobbyResponeHandler.LeaveRoom(com);
				}
				inLobby = false;
				wnd.ChangeToMenu(com, username, wnd);

			}
			catch
			{
				wnd.ChangeToError(wnd);
			}
		}
		private void OnCloseClick(object sender, RoutedEventArgs e)
		{
			try
			{
				lock (this.locker)
				{
					LobbyResponeHandler.CloseRoom(this.com);
				}
				inLobby = false;
				wnd.ChangeToMenu(com, username, wnd);

			}
			catch
			{
				wnd.ChangeToError(wnd);
			}
		}
		public void CheckIfGameHasStarted()
		{
			bool hasGameStarted;
			hasGameStarted = false;
			try
			{
				while (inLobby)
				{
					lock (this.locker)
					{
						if (inLobby)
							hasGameStarted = LobbyResponeHandler.checkIfGameHasStarted(com);

							if (hasGameStarted)
							{
								this.Dispatcher.Invoke(() =>
								{
									inLobby = false;
									GetQuestionResponse response = GameResponeHandler.getNextQuestion(com);
									wnd.ChangeToQuestion(this.questionTime, response.question, response.Answers, com, wnd, 1, this.numOfQuestions);
								});
							}
						
					}
					Thread.Sleep(1000);
				}
			}
			catch
            {
				this.Dispatcher.Invoke(() =>
				{
					wnd.ChangeToError(wnd);
				});
			}

		}
			public void ScreenRefresh()
		{
			try
			{
				while (inLobby)
				{
					GetPlayersInRoomResponse room;
					room.playersInRoom = null;
					room.status = 0;
					Thread.Sleep(3000);
					lock (this.locker)
					{
						if (inLobby)
							room = LobbyResponeHandler.GetPlayersInRoom(com, this.roomId);
					}
					this.Dispatcher.Invoke(() =>
					{
						if (inLobby)
							ListOfConnected.ItemsSource = room.playersInRoom;
					});
					if (room.status == Constants.Fail && !this.isLeader)//Means that the room was closed!
					{
						this.Dispatcher.Invoke(() =>
						{
							if (inLobby)
								wnd.ChangeToMenu(com, username, wnd);
						});
						inLobby = false;
					}
				}
			}
			catch
			{
				this.Dispatcher.Invoke(() =>
				{
					wnd.ChangeToError(wnd);
				});
			}
		}
	}
}
