using System.Windows;

namespace ES_FrontEnd
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private Controller m_controller;

        public MainWindow()
        {
            InitializeComponent();
            m_controller = new Controller(this);
        }


        private void OnBtn_ScenarioControl_Click(object sender, RoutedEventArgs e)
        {
            m_controller.ShowScenarioControl();
        }

        private void OnBtn_ClientSettings_Click(object sender, RoutedEventArgs e)
        {
            m_controller.ShowClientSettings();
        }

        private void OnBtn_WeatherSettings_Click(object sender, RoutedEventArgs e)
        {
            m_controller.ShowWeatherSettings();
        }

        private void OnBtn_ShipSettings_Click(object sender, RoutedEventArgs e)
        {
            m_controller.ShowShipSettings();
        }
    }
}
