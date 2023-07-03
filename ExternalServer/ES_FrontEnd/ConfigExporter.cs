using Newtonsoft.Json.Linq;
using System.IO;

namespace ES_FrontEnd
{
    public class ConfigExporter
    {
        private DataModel m_model;

        public ConfigExporter(DataModel _model)
        {
            m_model = _model;
        }


        /// <summary>
        /// Gather all Informations from the FrontEnd
        /// & put it all into a neat JObject for easy reading and saving
        /// </summary>
        /// <param name="_path"> Check Controller in case you wanna change</param>
        public void ExportConfig(string _path)
        {
            JObject scenarioConfig = new JObject();
            scenarioConfig["MaxClients"] = 6;
            scenarioConfig["ServerDataPort"] = m_model.ScenarioConfiguration.ServerDataPort;
            scenarioConfig["ServerCommandPort"] = m_model.ScenarioConfiguration.ServerCommandPort;
            scenarioConfig["WeatherSettings"] = (int)m_model.ScenarioConfiguration.WeatherSetting;
            scenarioConfig["Time"] = m_model.ScenarioConfiguration.Time;


            JArray clients = new JArray();
            foreach (Client client in m_model.Clients)
            {
                JObject clientObject = new JObject();
                clientObject["ID"] = client.ID;
                clientObject["IP"] = client.IP;
                clientObject["ClientDataPort"] = client.ClientDataPort;
                clientObject["ClientCommandPort"] = client.ClientCommandPort;
                clientObject["ClientType"] = (int)client.ClientType;

                clients.Add(clientObject);
            }

            scenarioConfig["Clients"] = clients;

            CreateJsonFile(_path, scenarioConfig);
        }


        /// <summary>
        /// Creates JsonFile and writes the content inside
        /// </summary>
        /// <param name="_path"> Path of the config file (check Controller) </param>
        /// <param name="_jObject"> JObject that should have all Parameters from above saved up</param>
        public void CreateJsonFile(string _path, JObject _jObject)
        {
            if (File.Exists(_path))
            {
                File.WriteAllText(_path, _jObject.ToString());
            }
            else
            {
                File.WriteAllText(_path, _jObject.ToString());
            }
        }
    }
}
