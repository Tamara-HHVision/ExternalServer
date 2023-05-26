using System.Windows.Controls;

namespace ES_FrontEnd.UserControls
{
    /// <summary>
    /// Interaction logic for UC_Ship.xaml
    /// </summary>
    public partial class UC_Ship : UserControl
    {
        Controller m_controller;

        public UC_Ship(Controller _controller)
        {
            InitializeComponent();
            m_controller = _controller;
        }
    }
}
