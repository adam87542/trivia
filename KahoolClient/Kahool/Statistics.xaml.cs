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
	/// Interaction logic for Statistics.xaml
	/// </summary>
	public partial class Statistics : Page
	{
		private MenuWindow wnd;
		private Communicator com;
		public Statistics(Communicator com, MenuWindow wnd)
		{
			try
			{
				this.com = com;
				this.wnd = wnd;
				InitializeComponent();
				StatisticsResponse response = StatisticsResponseHandler.GetStatisticsOfUser(com);
				GreetingLabel.Content += response.username;
				NumOfPlayedGamesLabel.Content += response.numPlayedGames.ToString();
				CorrectAnswerCountLabel.Content += response.correctAnswerCount.ToString();
				WrongAnswersLabel.Content += response.wrongAnswerCount.ToString();
				AverageAnswerTimeLabel.Content += response.averangeAnswerTime.ToString();
			}
			catch
			{
				//Shuhman and adam add here the wnd.ChangeToError()
			}
		}

		private void OnMenuClick(object sender, RoutedEventArgs e)
		{
			//Shuhman delete the username from every page, EVERY single one
			wnd.ChangeToMenu(com, "", wnd);
		}
	}
}
