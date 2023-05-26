using System.Windows.Controls;

namespace ES_FrontEnd.UserControls
{
    /// <summary>
    /// Interaction logic for UC_Weather.xaml
    /// </summary>
    public partial class UC_Weather : UserControl
    {
        Controller m_controller;
        public UC_Weather(Controller _controller)
        {
            InitializeComponent();
            m_controller = _controller;
        }
    }
}
