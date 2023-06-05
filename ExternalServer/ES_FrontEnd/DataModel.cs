namespace ES_FrontEnd
{
    public class DataModel
    {
        private Client m_client;
        private ScenarioConfiguration m_scenarioConfiguration;

        public Client Client => m_client;
        public ScenarioConfiguration ScenarioConfiguration => m_scenarioConfiguration;

        private int m_trackedClientID = 0;
        private int m_serverDataPort;
        private int m_serverCommandPort;


        public Client CreateClient(string _ip, int _commandPort, int _dataPort, EClientType _clientType)
        {
            // Generate new ID for the Client
            int newClientID = m_trackedClientID++;
            //Update counter
            m_trackedClientID = newClientID;

            // create client and return it
            Client client = new Client(newClientID, _ip, _commandPort, _dataPort, _clientType);
            return client;
        }


        public void GetServerPorts(int _serverDataPort, int _serverCommandPort)
        {
            m_serverDataPort = _serverDataPort;
            m_serverCommandPort = _serverCommandPort;
        }


        public void SaveConfigToJson()
        {
            ConfigExporter configExporter = new ConfigExporter(this);
            configExporter.ExportConfig("");
        }
    }
}
