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
        private Communicator com;
        private string username;
        public MenuWindow(Communicator com, string username)
        {
            InitializeComponent();
            this.com = com;
            this.username = username;
        }
        private void OnCreateRoomClick(object sender, RoutedEventArgs e)
        {

        }

        private void OnJoinRoomClick(object sender, RoutedEventArgs e)
        {
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
    }
}
