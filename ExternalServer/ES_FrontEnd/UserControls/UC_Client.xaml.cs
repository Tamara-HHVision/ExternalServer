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
            m_controller.AddClientWindow();
        }
    }
}
