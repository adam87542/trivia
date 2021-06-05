﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
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
	/// Interaction logic for MainWindow.xaml
	/// </summary>
	public partial class MainWindow : Window
	{
		public Communicator com;

		public MainWindow()
		{
			InitializeComponent();
		}

		public void Signup_Click(object sender, RoutedEventArgs e)
		{
			App.Current.MainWindow.Hide();
			SignUpWindow wnd = new SignUpWindow();
			wnd.ShowDialog();
		}

		public void EndRunning(object sender, RoutedEventArgs e)
		{
			System.Windows.Application.Current.Shutdown();
		}
		private void Window_MouseDown(object sender, MouseButtonEventArgs e)
		{
			if (e.ChangedButton == MouseButton.Left)
				this.DragMove();
		}

        private void OnLoginClick(object sender, RoutedEventArgs e)
        {
			LoginRequest request;
			request.username = UserNameBox.Text;
			request.password = PasswordBox.Password;
			bool IsSucceed = LoginResponeHandler.CheckLogin(request);
			if (IsSucceed)
			{
				App.Current.MainWindow.Hide();
				MenuWindow wnd = new MenuWindow();
				wnd.ShowDialog();
			}
            else
            {
				MessageLabel.Content = "Failed To Login , try agian!";
            }
		}
    }
}
