using System;
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
using System.Threading;

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
			Thread comThread = new Thread(initiateCommunication);
			comThread.Start();
		}

		private void retryCommunication(object sender, KeyEventArgs e)
		{
			if(e.Key == Key.F5 && com == null)
			{
				Thread comThread = new Thread(initiateCommunication);
				comThread.Start();
			}
		}

		public void initiateCommunication()
		{
			try
			{
				com = new Communicator();
				this.Dispatcher.Invoke(() =>
				{
					MessageLabel.Content = "";
				});
			}
			catch (Exception ex)
			{
				this.Dispatcher.Invoke(() =>
				{
					MessageLabel.Content = ex.Message + " - Click here to retry";
				});
				com = null;
			}
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
			App.Current.MainWindow.Hide();
			MenuWindow wnd = new MenuWindow();
			wnd.ShowDialog();
		}
    }
}
