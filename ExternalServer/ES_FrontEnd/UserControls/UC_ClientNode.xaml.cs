using System.Windows.Controls;
using System.Windows.Media.Imaging;

namespace ES_FrontEnd.UserControls
{
    /// <summary>
    /// Interaction logic for UC_ClientNode.xaml
    /// </summary>
    public partial class UC_ClientNode : UserControl
    {
        private Controller m_controller;

        public UC_ClientNode(Controller _controller, int _id, EClientType _clientType)
        {
            InitializeComponent();

            m_controller = _controller;

            Lbl_ClientID.Content = _id;
            Lbl_ClientType.Content = _clientType.ToString().ToUpper();

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

                case EClientType.CONTROLCENTER:
                Img_ClientType.Source = new BitmapImage(new System.Uri("pack://application:,,,/ES_FrontEnd;component/Resources/Icons/Icn_VR.png"));
                break;

                default:
                Img_ClientType.Source = new BitmapImage(new System.Uri("pack://application:,,,/ES_FrontEnd;component/Resources/Icons/Icn_Ship.png"));
                break;
            }
        }
    }
}
