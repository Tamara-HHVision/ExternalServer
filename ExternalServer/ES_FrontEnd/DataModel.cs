using System.Collections.Generic;

namespace ES_FrontEnd
{
    public class DataModel
    {
        private List<Client> m_clients = new List<Client>();

        private ScenarioConfiguration m_scenarioConfiguration = new ScenarioConfiguration();

        public List<Client> Clients => m_clients;
        public ScenarioConfiguration ScenarioConfiguration => m_scenarioConfiguration;

        private int m_trackedClientID = 0;


        public int CreateClient(string _ip, int _commandPort, int _dataPort, EClientType _clientType)
        {
            // Generate new ID for the Client
            int newClientID;
            m_trackedClientID++;

            newClientID = m_trackedClientID;
            //Update counter
            m_trackedClientID = newClientID;

            // create client and return it
            Client client = new Client(newClientID, _ip, _commandPort, _dataPort, _clientType);
            m_clients.Add(client);
            return client.ID;
        }

        public void OverrideClient(Client _client)
        {
            m_clients[_client.ID - 1].IP = _client.IP;
            m_clients[_client.ID - 1].ClientCommandPort = _client.ClientCommandPort;
            m_clients[_client.ID - 1].ClientDataPort = _client.ClientDataPort;
            m_clients[_client.ID - 1].ClientType = _client.ClientType;
        }

        public void GetServerPorts(int _serverDataPort, int _serverCommandPort)
        {
            ScenarioConfiguration.ServerDataPort = _serverDataPort;
            ScenarioConfiguration.ServerCommandPort = _serverCommandPort;
        }

        public void GetWeatherAndTimeSetting(EWeatherSetting _weather, int _time)
        {
            ScenarioConfiguration.WeatherSetting = _weather;
            ScenarioConfiguration.Time = _time;
        }

        public void SaveConfigToJson(string _path)
        {
            ConfigExporter configExporter = new ConfigExporter(this);
            configExporter.ExportConfig(_path);
        }

    }
}
