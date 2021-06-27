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
using System.Windows.Shapes;

namespace Kahool
{
	/// <summary>
	/// Interaction logic for MenuWindow.xaml
	/// </summary>
	public partial class MenuWindow : Window
	{
		Communicator com;
		string username;

		public MenuWindow(Communicator com, string username)
		{
			InitializeComponent();
			this.Content = new MenuPage(com, username, this);
			this.com = com;
			this.username = username;
		}

		public void ChangeToLobby(bool isLeader, string username, string roomId, string roomName, string timeBetweenQuestions, string difficulty, string numOfQuestions, Communicator com, MenuWindow wnd)
		{
			this.Content = new LobbyRoom(isLeader, username, roomId, roomName, timeBetweenQuestions, difficulty, numOfQuestions, com, wnd);
		}

		public void ChangeToMenu(Communicator com, string username, MenuWindow wnd)
		{
			this.Content = new MenuPage(com, username, wnd);
		}

		public void ChangeToError( MenuWindow wnd)
		{
			this.Content = new ErrorPage(wnd);
		}

		private void Window_MouseDown(object sender, MouseButtonEventArgs e)
		{
			if (e.ChangedButton == MouseButton.Left)
				this.DragMove();
		}
	}
}
