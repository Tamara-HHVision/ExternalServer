using System.Windows.Controls;

namespace ES_FrontEnd.UserControls
{
    /// <summary>
    /// Interaction logic for UC_Weather.xaml
    /// </summary>
    public partial class UC_Weather : UserControl
    {
        Controller m_controller;

        EWeatherSetting m_weather;

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
                        break;
                    case "Btn_PartlyCloudy":
                        m_weather = EWeatherSetting.PARTLYCLOUDY;
                        break;
                    case "Btn_Cloudy":
                        m_weather = EWeatherSetting.CLOUDY;
                        break;
                    case "Btn_Overcast":
                        m_weather = EWeatherSetting.OVERCAST;
                        break;
                    case "Btn_Foggy":
                        m_weather = EWeatherSetting.FOGGY;
                        break;
                    case "Btn_LightRain":
                        m_weather = EWeatherSetting.LIGHTRAIN;
                        break;
                    case "Btn_Rain":
                        m_weather = EWeatherSetting.RAIN;
                        break;
                    case "Btn_Thunderstorm":
                        m_weather = EWeatherSetting.THUNDERSTORM;
                        break;
                    case "Btn_LightSnow":
                        m_weather = EWeatherSetting.LIGHTSNOW;
                        break;
                    case "Btn_Snow":
                        m_weather = EWeatherSetting.SNOW;
                        break;
                    case "Btn_Blizzard":
                        m_weather = EWeatherSetting.BLIZZARD;
                        break;
                    default:
                        break;

                }
            }
        }


        private void OnBtn_SaveWeather_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            m_controller.GetWeatherSetting(m_weather);

            m_controller.SaveConfiguration();
        }
    }
}
