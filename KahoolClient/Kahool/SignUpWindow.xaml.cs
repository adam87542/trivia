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
	/// Interaction logic for Window1.xaml
	/// </summary>
	public partial class SignUpWindow : Window
	{
		private Communicator com;
		public SignUpWindow(Communicator com)
		{
			InitializeComponent();
			this.com = com;
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

		public string CheckIfPasswordsAreMatching(string password, string confirmPassword)
		{
			if (password != confirmPassword)
				return "Password's Are not Matching!";

			return null;
		}

		private void VerifySignUp(object sender, RoutedEventArgs e)
		{
			try
			{
				string signupResult = CheckIfPasswordsAreMatching(PasswordBox.Password, PasswordBox_Copy.Password);
				if (signupResult != null)
					MessageLabelSignup.Content = signupResult;
				else
				{
					SignupRequest request = new SignupRequest(UserNameBox.Text, PasswordBox.Password, EmailBox.Text);
					//Sign up was a success
					string responeMsg = LoginResponeHandler.CheckSignUp(com, request);
					if (responeMsg == null)
					{
						this.Visibility = Visibility.Collapsed;	
						MenuWindow wnd = new MenuWindow(this.com, UserNameBox.Text);
						wnd.ShowDialog();
					}
					else
						MessageLabelSignup.Content = responeMsg;

				}
			}
			catch
			{
				MessageLabelSignup.Content = "Can't reach server, returning in 5 seconds to login";
				System.Threading.Thread.Sleep(5000);
				this.Visibility = Visibility.Collapsed;
				MainWindow wnd = new MainWindow();
				wnd.ShowDialog();
			}
		}
	}
}
