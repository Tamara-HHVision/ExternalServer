using System.Windows;

namespace ES_FrontEnd.Windows
{
    /// <summary>
    /// Interaction logic for W_AddNewClient.xaml
    /// </summary>
    public partial class W_AddNewClient : Window
    {
        private Controller m_controller;

        private string m_clientIP = "127.0.0.1";
        private int m_clientCommandPort;
        private int m_clientDataPort;
        private EClientType m_clientType;


        public W_AddNewClient(Controller _controller)
        {
            InitializeComponent();
            m_controller = _controller;
        }

        private void OnBtn_CloseClientWindow_Click(object sender, RoutedEventArgs e)
        {
            m_controller.CloseAddClientWindow(this);
        }

        private void OnBtn_SaveClient_Click(object sender, RoutedEventArgs e)
        {
            m_controller.CreateNewClient(m_clientIP, m_clientCommandPort, m_clientDataPort, m_clientType);
            m_controller.CloseAddClientWindow(this);
        }

        #region --- User Input ---

        private void OnTxtBx_ClientIP_TextChanged(object sender, System.Windows.Controls.TextChangedEventArgs e)
        {
            m_clientIP = TxtBx_ClientIP.Text;
        }

        private void OnTxtBx_ClientCommandPort_TextChanged(object sender, System.Windows.Controls.TextChangedEventArgs e)
        {
            int tmpValue;
            bool success = int.TryParse(TxtBx_ClientCommandPort.Text, out tmpValue);

            m_clientCommandPort = tmpValue; ;
        }

        private void OnTxtBx_ClientDataPort_TextChanged(object sender, System.Windows.Controls.TextChangedEventArgs e)
        {
            int tmpValue;
            bool success = int.TryParse(TxtBx_ClientDataPort.Text, out tmpValue);

            m_clientDataPort = tmpValue;
        }

        private void OnBtn_ShipType_Click(object sender, RoutedEventArgs e)
        {
            ToggleButton.Content = "Ship";
            m_clientType = EClientType.VESSEL;
            Ppp_ClientType.IsOpen = !Ppp_ClientType.IsOpen;
        }

        private void OnBtn_PedestrianType_Click(object sender, RoutedEventArgs e)
        {
            ToggleButton.Content = "Pedestrian";
            m_clientType = EClientType.PEDESTRIAN;
            Ppp_ClientType.IsOpen = !Ppp_ClientType.IsOpen;

        }

        private void OnBtn_VRType_Click(object sender, RoutedEventArgs e)
        {
            ToggleButton.Content = "VR";
            m_clientType |= EClientType.VR;
            Ppp_ClientType.IsOpen = !Ppp_ClientType.IsOpen;

        }
        #endregion


        private void ToggleButton_Click(object sender, RoutedEventArgs e)
        {
            //MyComboBox.IsDropDownOpen = !MyComboBox.IsDropDownOpen;

            Ppp_ClientType.IsOpen = !Ppp_ClientType.IsOpen;
        }


    }
}
