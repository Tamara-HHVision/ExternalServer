using System.Windows.Controls;

namespace ES_FrontEnd.UserControls
{
    /// <summary>
    /// Interaction logic for US_Scenario.xaml
    /// </summary>
    public partial class UC_Scenario : UserControl
    {
        Controller m_controller;

        public UC_Scenario(Controller _controller)
        {
            InitializeComponent();
            m_controller = _controller;
        }
    }
}
