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

    class ScenarioConfiguration
    {
        private int m_serverCommandPort;
        private int m_serverDataPort;
        private int m_time;

        private EWeatherSetting m_weatherSetting;
    }
}
