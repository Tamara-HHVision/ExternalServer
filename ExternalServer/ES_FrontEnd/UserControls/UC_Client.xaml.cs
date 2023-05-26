using ES_FrontEnd.Windows;
using System.Windows;
using System.Windows.Controls;

namespace ES_FrontEnd.UserControls
{
    /// <summary>
    /// Interaction logic for UC_Client.xaml
    /// </summary>
    public partial class UC_Client : UserControl
    {
        Controller m_controller;

        public UC_Client(Controller _controller)
        {
            InitializeComponent();
            m_controller = _controller;
        }

        private void OnBtn_AddClient_Click(object sender, RoutedEventArgs e)
        {
            // Create a new instance of the window to be spawned
            W_AddNewClient newClientWindow = new W_AddNewClient(m_controller);

            // Set the startup location of the window to center with respect to the owner
            newClientWindow.WindowStartupLocation = WindowStartupLocation.CenterOwner;

            // Set the owner of the window
            newClientWindow.Owner = Application.Current.MainWindow;

            // Show the window
            newClientWindow.Show();
        }
    }
}
