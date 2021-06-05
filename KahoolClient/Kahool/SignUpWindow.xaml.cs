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
	public partial class SignUpWindow: Window
	{
		public SignUpWindow()
		{
			InitializeComponent();
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

		public string CheckSignUpContent(string username, string email, string password, string confirmPassword)
		{
			if (password != confirmPassword)
				return "Password's Are not Matching!";
			else if (password.Length < Constants.MIN_PASSWORD_LENGTH || password.Length > Constants.MAX_PASSWORD_LENGTH)
				return "Password length is 8-20!";
			else if (username.Length < Constants.MIN_USERNAME_LENGTH || username.Length > Constants.MAX_USERNAME_LENGTH)
				return "Username length is 6-15";
			try
			{
				var addr = new System.Net.Mail.MailAddress(email);
			}
			catch
			{
				return "Email not valid!";
			}

			return null;
		}

		private void VerifySignUp(object sender, RoutedEventArgs e)
		{
			string signupResult = CheckSignUpContent(UserNameBox.Text, EmailBox.Text, PasswordBox.Password, PasswordBox_Copy.Password);
			if (signupResult != null)
				MessageLabel.Content = signupResult;
			else
			{
				SignupRequest request = new SignupRequest();
				request.email = EmailBox.Text;
				request.password = PasswordBox.Password;
				request.username = UserNameBox.Text;
				bool IsSucceed = LoginResponeHandler.CheckSignUp(request);

			}
		}
    }
}
