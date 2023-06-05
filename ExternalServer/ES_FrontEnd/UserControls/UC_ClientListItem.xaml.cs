using System.Windows.Controls;
using System.Windows.Media.Imaging;

namespace ES_FrontEnd.UserControls
{
    /// <summary>
    /// Interaction logic for UC_ClientListItem.xaml
    /// </summary>
    public partial class UC_ClientListItem : UserControl
    {
        public UC_ClientListItem(string _ip, int _commandPort, int _dataPort, EClientType _clientType)
        {
            InitializeComponent();

            Lbl_ClientIP.Content = _ip;
            Lbl_ClientCommandPort.Content = _commandPort;
            Lbl_ClientDataPort.Content = _dataPort;
            Lbl_ClientType.Content = _clientType.ToString();

            CheckClientType(_clientType);
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
    }
}
