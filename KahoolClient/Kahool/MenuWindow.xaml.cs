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
            CreateRoomRequest createRoomRequest;
            createRoomRequest.roomName = RoomNameBox.Text;
            createRoomRequest.difficulty = this.DifficultyBox.Text;
            createRoomRequest.answerTimeOut = uint.Parse(TimerBox.Text);
            createRoomRequest.maxUsers = uint.Parse(MaxPlayersBox.Text);
            createRoomRequest.questionCount = uint.Parse(NumberOfQuestionsBox.Text);

            CreateRoomResponse response = MenuResponeHandler.CreateRoom(com, createRoomRequest);

            if (response.status == Constants.Success)
                this.Content = new LobbyRoom(true, response.roomId.ToString() , response.roomName ,createRoomRequest.answerTimeOut.ToString(),createRoomRequest.difficulty,createRoomRequest.questionCount.ToString(),com);
            else
                MessageLabelCreate.Content = "Couldn't create room, please try again later";
        }

        private void OnJoinRoomClick(object sender, RoutedEventArgs e)
        {
            JoinRoomRequest request;
            request.roomId = Convert.ToUInt32(RoomIdBox.Text);

            JoinRoomResponse response = MenuResponeHandler.JoinRoom(com, request);


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
