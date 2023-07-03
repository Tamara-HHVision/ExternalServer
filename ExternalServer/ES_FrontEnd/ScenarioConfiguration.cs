namespace ES_FrontEnd
{
    public enum EWeatherSetting
    {
        CLEARSKY,
        PARTLYCLOUDY,
        CLOUDY,
        OVERCAST,
        FOGGY,
        LIGHTRAIN,
        RAIN,
        THUNDERSTORM,
        LIGHTSNOW,
        SNOW,
        BLIZZARD
    }

    public class ScenarioConfiguration
    {
        public int ServerCommandPort { get; set; }
        public int ServerDataPort { get; set; }
        public int Time { get; set; }

        public EWeatherSetting WeatherSetting { get; set; }

        public ScenarioConfiguration(/*int _serverCommandPort, int _serverDataPort, int _time, EWeatherSetting _weatherSetting*/)
        {
            //ServerCommandPort = _serverCommandPort;
            //ServerDataPort = _serverDataPort;
            //Time = _time;
            //WeatherSetting = _weatherSetting;
        }
    }
}
