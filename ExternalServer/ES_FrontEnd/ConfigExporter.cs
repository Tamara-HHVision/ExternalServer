using Newtonsoft.Json.Linq;

namespace ES_FrontEnd
{
    public class ConfigExporter
    {
        private DataModel m_model;

        public ConfigExporter(DataModel _model)
        {
            m_model = _model;
        }

        public void ExportConfig(string _path)
        {
            JObject scenarioConfig = new JObject();
            scenarioConfig["MaxClients"] = 6;
            scenarioConfig["ServerDataPort"] = m_model.ScenarioConfiguration.ServerDataPort;
            scenarioConfig["ServerCommandPort"] = m_model.ScenarioConfiguration.ServerCommandPort;
            scenarioConfig["WeatherSettings"] = (int)m_model.ScenarioConfiguration.WeatherSetting;
            scenarioConfig["Time"] = m_model.ScenarioConfiguration.Time;


        }
    }
}
