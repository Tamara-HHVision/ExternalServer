﻿using System;
using System.Windows;
using System.Windows.Controls;

namespace ES_FrontEnd.UserControls
{
    /// <summary>
    /// Interaction logic for US_Scenario.xaml
    /// </summary>
    public partial class UC_Scenario : UserControl
    {
        Controller m_controller;

        private int m_serverDataPort = 5000;
        private int m_serverCommandPort = 5001;

        public UC_Scenario(Controller _controller)
        {
            InitializeComponent();
            m_controller = _controller;
        }

        private void OnBtn_SaveConfig_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            m_controller.GetServerPorts(m_serverDataPort, m_serverCommandPort);

            m_controller.SaveConfiguration();
        }

        private void OnBtn_StartScenario_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            try
            {
                if (BackendInterface.LoadConfiguration(Controller.jsonPath))
                {
                    Status.Log("Config successfully loaded!");

                    MessageBox.Show("Started!");
                    BackendInterface.StartUnrealLoop();

                    Status.Log("Szenario started!");
                }
                else
                {
                    Status.Log("ERROR: Couldn't load config");
                }
            }
            catch (Exception _exception)
            {
                MessageBox.Show(_exception.ToString());
            }


        }

        private void OnStopScenario_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            BackendInterface.ShutDownBackend();
            Status.Log("Shut down!");
        }

        private void OnTxtBx_ServerDataPort_TextChanged(object sender, TextChangedEventArgs e)
        {
            int tmpValue;
            bool success = int.TryParse(TxtBx_ServerDataPort.Text, out tmpValue);

            m_serverDataPort = tmpValue;
        }

        private void OnTxtBx_ServerCommandPort_TextChanged(object sender, TextChangedEventArgs e)
        {
            int tmpValue;
            bool success = int.TryParse(TxtBx_ServerCommandPort.Text, out tmpValue);

            m_serverCommandPort = tmpValue;
        }
    }
}
