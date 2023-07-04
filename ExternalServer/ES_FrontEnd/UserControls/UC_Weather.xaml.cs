using System.Windows.Controls;
using System.Windows.Media;

namespace ES_FrontEnd.UserControls
{
    /// <summary>
    /// Interaction logic for UC_Weather.xaml
    /// </summary>
    public partial class UC_Weather : UserControl
    {
        Controller m_controller;

        EWeatherSetting m_weather;
        private Button? m_selectedButton;

        public UC_Weather(Controller _controller)
        {
            InitializeComponent();
            m_controller = _controller;
        }


        private void OnBtn_ChooseWeather_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            Button clickedButton = sender as Button;

            if (clickedButton != null)
            {
                switch (clickedButton.Name)
                {
                    case "Btn_ClearSky":
                        m_weather = EWeatherSetting.CLEARSKY;
                        clickedButton.BorderBrush = new SolidColorBrush(Color.FromRgb(250, 150, 0));
                        break;
                    case "Btn_PartlyCloudy":
                        m_weather = EWeatherSetting.PARTLYCLOUDY;
                        clickedButton.BorderBrush = new SolidColorBrush(Color.FromRgb(250, 150, 0));
                        break;
                    case "Btn_Cloudy":
                        m_weather = EWeatherSetting.CLOUDY;
                        clickedButton.BorderBrush = new SolidColorBrush(Color.FromRgb(250, 150, 0));
                        break;
                    case "Btn_Overcast":
                        m_weather = EWeatherSetting.OVERCAST;
                        clickedButton.BorderBrush = new SolidColorBrush(Color.FromRgb(250, 150, 0));
                        break;
                    case "Btn_Foggy":
                        m_weather = EWeatherSetting.FOGGY;
                        clickedButton.BorderBrush = new SolidColorBrush(Color.FromRgb(250, 150, 0));
                        break;
                    case "Btn_LightRain":
                        m_weather = EWeatherSetting.LIGHTRAIN;
                        clickedButton.BorderBrush = new SolidColorBrush(Color.FromRgb(250, 150, 0));
                        break;
                    case "Btn_Rain":
                        m_weather = EWeatherSetting.RAIN;
                        clickedButton.BorderBrush = new SolidColorBrush(Color.FromRgb(250, 150, 0));
                        break;
                    case "Btn_Thunderstorm":
                        m_weather = EWeatherSetting.THUNDERSTORM;
                        clickedButton.BorderBrush = new SolidColorBrush(Color.FromRgb(250, 150, 0));
                        break;
                    case "Btn_LightSnow":
                        m_weather = EWeatherSetting.LIGHTSNOW;
                        clickedButton.BorderBrush = new SolidColorBrush(Color.FromRgb(250, 150, 0));
                        break;
                    case "Btn_Snow":
                        m_weather = EWeatherSetting.SNOW;
                        clickedButton.BorderBrush = new SolidColorBrush(Color.FromRgb(250, 150, 0));
                        break;
                    case "Btn_Blizzard":
                        m_weather = EWeatherSetting.BLIZZARD;
                        clickedButton.BorderBrush = new SolidColorBrush(Color.FromRgb(250, 150, 0));
                        break;
                    default:
                        break;

                }
            }


            if (clickedButton == m_selectedButton)
            {
                m_selectedButton = null;
                clickedButton.BorderBrush = Brushes.Transparent;
            }
            else
            {
                if (m_selectedButton != null)
                {
                    m_selectedButton.BorderBrush = Brushes.Transparent;
                }

                m_selectedButton = clickedButton;
            }


        }


        private void OnBtn_SaveWeather_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            m_controller.GetWeatherSetting(m_weather);

            m_controller.SaveConfiguration();
        }
    }
}
