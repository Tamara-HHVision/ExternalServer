using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace ES_FrontEnd
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private Controller m_controller;

        private Button m_lastPressedButton;

        public MainWindow()
        {
            InitializeComponent();
            m_controller = new Controller(this);
        }


        private void OnBtn_ScenarioControl_Click(object sender, RoutedEventArgs e)
        {
            m_controller.ShowScenarioControl();

            // Revert the background color of the last pressed button, if available
            if (m_lastPressedButton != null)
            {
                m_lastPressedButton.Background = Brushes.Transparent;
                m_lastPressedButton.BorderBrush = Brushes.Transparent;
            }

            // Set the background color of the current button
            Button button = (Button)sender;
            button.Background = new SolidColorBrush(Color.FromRgb(0, 0, 0)); // Custom Color code: Black
            button.BorderBrush = new SolidColorBrush(Color.FromRgb(250, 150, 0)); // custom Color code: Orange

            // Update the last pressed button
            m_lastPressedButton = button;

            button.UpdateLayout();
        }

        private void OnBtn_ClientSettings_Click(object sender, RoutedEventArgs e)
        {
            m_controller.ShowClientSettings();

            // Revert the background color of the last pressed button, if available
            if (m_lastPressedButton != null)
            {
                m_lastPressedButton.Background = Brushes.Transparent;
                m_lastPressedButton.BorderBrush = Brushes.Transparent;
            }

            // Set the background color of the current button
            Button button = (Button)sender;
            button.Background = new SolidColorBrush(Color.FromRgb(0, 0, 0)); // Custom Color code: Black
            button.BorderBrush = new SolidColorBrush(Color.FromRgb(250, 150, 0)); // custom Color code: Orange

            // Update the last pressed button
            m_lastPressedButton = button;
        }

        private void OnBtn_WeatherSettings_Click(object sender, RoutedEventArgs e)
        {
            m_controller.ShowWeatherSettings();

            // Revert the background color of the last pressed button, if available
            if (m_lastPressedButton != null)
            {
                m_lastPressedButton.Background = Brushes.Transparent;
                m_lastPressedButton.BorderBrush = Brushes.Transparent;
            }

            // Set the background color of the current button
            Button button = (Button)sender;
            button.Background = new SolidColorBrush(Color.FromRgb(0, 0, 0)); // Custom Color code: Black
            button.BorderBrush = new SolidColorBrush(Color.FromRgb(250, 150, 0)); // custom Color code: Orange

            // Update the last pressed button
            m_lastPressedButton = button;
        }

        private void OnBtn_ShipSettings_Click(object sender, RoutedEventArgs e)
        {
            m_controller.ShowShipSettings();

            // Revert the background color of the last pressed button, if available
            if (m_lastPressedButton != null)
            {
                m_lastPressedButton.Background = Brushes.Transparent;
                m_lastPressedButton.BorderBrush = Brushes.Transparent;
            }

            // Set the background color of the current button
            Button button = (Button)sender;
            button.Background = new SolidColorBrush(Color.FromRgb(0, 0, 0)); // Custom Color code: Black
            button.BorderBrush = new SolidColorBrush(Color.FromRgb(250, 150, 0)); // custom Color code: Orange

            // Update the last pressed button
            m_lastPressedButton = button;
        }
    }
}
