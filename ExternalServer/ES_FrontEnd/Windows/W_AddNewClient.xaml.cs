using System.Windows;

namespace ES_FrontEnd.Windows
{
    /// <summary>
    /// Interaction logic for W_AddNewClient.xaml
    /// </summary>
    public partial class W_AddNewClient : Window
    {
        Controller m_controller;

        public W_AddNewClient(Controller _controller)
        {
            InitializeComponent();
            m_controller = _controller;
        }

        private void OnBtn_CloseClientWindow_Click(object sender, RoutedEventArgs e)
        {
            m_controller.CloseAddClientWindow(this);
        }
    }
}
