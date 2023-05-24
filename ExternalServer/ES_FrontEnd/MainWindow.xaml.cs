using ES_FrontEnd.UserControls;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace ES_FrontEnd
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void OnBtn_WeatherSettings_Click(object sender, RoutedEventArgs e)
        {
            Cnvs_MainView.Children.Clear();
            UC_Weather uc_weather = new UC_Weather();

            Cnvs_MainView.Children.Add(uc_weather);
        }

        private void OnBtn_ScenarioControl_Click(object sender, RoutedEventArgs e)
        {
            Cnvs_MainView.Children.Clear();

            UC_Scenario uc_Scenario = new UC_Scenario();

            Cnvs_MainView.Children.Add(uc_Scenario);
        }
    }
}
