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
using System.Threading;

namespace Kahool
{
    /// <summary>
    /// Interaction logic for Question.xaml
    /// </summary>
    public partial class Question : Page
    {
        private int time; 
        public Question(int time)
        {
            this.time = time;
            InitializeComponent();

            Thread timer = new Thread(TimeCounter);
            timer.Start();
        }

        private void OnExitClick(object sender, RoutedEventArgs e)
        {

        }

        public void OnSubmitClick(object sender, RoutedEventArgs e)
        {

        }

        public void EndRunning(object sender, RoutedEventArgs e)
        {
            System.Windows.Application.Current.Shutdown();
        }

        public void TimeCounter()
        {
            for (int i = time; i >= 0; i--)
            {
                this.Dispatcher.Invoke(() =>
                {
                    Timer.Content = "Time: " + i.ToString();
                });
                Thread.Sleep(1000);
            }
        }
    }
}
