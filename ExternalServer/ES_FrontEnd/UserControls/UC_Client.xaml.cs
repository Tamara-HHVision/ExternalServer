using System.Windows;
using System.Windows.Controls;

namespace ES_FrontEnd.UserControls
{
    /// <summary>
    /// Interaction logic for UC_Client.xaml
    /// </summary>
    public partial class UC_Client : UserControl
    {
        public WrapPanel ClientWrapPanel { get; private set; }

        private Controller m_controller;


        public UC_Client(Controller _controller)
        {
            InitializeComponent();
            m_controller = _controller;
            ClientWrapPanel = Wrp_ClientList;
        }

        private void OnBtn_AddClient_Click(object sender, RoutedEventArgs e)
        {
            m_controller.AddClientWindow();
        }


    }
}
