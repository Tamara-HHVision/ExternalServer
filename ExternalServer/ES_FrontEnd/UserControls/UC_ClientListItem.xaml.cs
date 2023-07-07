using System.Windows.Controls;
using System.Windows.Media.Imaging;

namespace ES_FrontEnd.UserControls
{
    /// <summary>
    /// Interaction logic for UC_ClientListItem.xaml
    /// </summary>
    public partial class UC_ClientListItem : UserControl
    {
        private Controller m_controller;
        private int m_id;

        public UC_ClientListItem(Controller _controller, int _id, string _ip, int _commandPort, int _dataPort, EClientType _clientType)
        {
            InitializeComponent();
            m_controller = _controller;
            m_id = _id;

            Lbl_ClientIP.Content = _ip;
            Lbl_ClientCommandPort.Content = _commandPort;
            Lbl_ClientDataPort.Content = _dataPort;
            Lbl_ClientType.Content = _clientType.ToString();

            CheckClientType(_clientType);
            Lbl_ClientID.Content = $"Client {_id}";
        }

        private void CheckClientType(EClientType _clientType)
        {
            switch (_clientType)
            {
                case EClientType.VESSEL:
                Img_ClientType.Source = new BitmapImage(new System.Uri("pack://application:,,,/ES_FrontEnd;component/Resources/Icons/Icn_Ship.png"));
                break;

                case EClientType.PEDESTRIAN:
                Img_ClientType.Source = new BitmapImage(new System.Uri("pack://application:,,,/ES_FrontEnd;component/Resources/Icons/Icn_Pedestrian.png"));
                break;

                case EClientType.VR:
                Img_ClientType.Source = new BitmapImage(new System.Uri("pack://application:,,,/ES_FrontEnd;component/Resources/Icons/Icn_VR.png"));
                break;

                case EClientType.OPENSCENARIO:
                Img_ClientType.Source = new BitmapImage(new System.Uri("pack://application:,,,/ES_FrontEnd;component/Resources/Icons/Icn_Ship.png"));
                break;

                default:
                break;
            }
        }

        private void OnBtn_changeClient_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            m_controller.ChangeClient(m_id);
        }
    }
}
