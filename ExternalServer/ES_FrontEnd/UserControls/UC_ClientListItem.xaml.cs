using System.Windows.Controls;

namespace ES_FrontEnd.UserControls
{
    /// <summary>
    /// Interaction logic for UC_ClientListItem.xaml
    /// </summary>
    public partial class UC_ClientListItem : UserControl
    {
        public UC_ClientListItem(string _ip, int _commandPort, int _dataPort)
        {
            InitializeComponent();

            Lbl_ClientIP.Content = _ip;
            Lbl_ClientCommandPort.Content = _commandPort;
            Lbl_ClientDataPort.Content = _dataPort;

        }
    }
}
