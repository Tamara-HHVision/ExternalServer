using ES_FrontEnd.UserControls;
using ES_FrontEnd.Windows;
using System.Windows;

namespace ES_FrontEnd
{
    public class Controller
    {
        //public static string FileName = "config.json";
        //public static string BaseDirectory = AppDomain.CurrentDomain.BaseDirectory;
        //public static string FilePath = Path.Combine(BaseDirectory, FileName);

        public static string jsonPath = System.AppDomain.CurrentDomain.BaseDirectory + @"/config.json";


        private MainWindow m_view;
        private DataModel m_model;

        private W_AddNewClient? m_newClientWindow = null;

        private UC_Scenario m_uc_scenario;
        private UC_Client m_uc_client;
        private UC_Weather m_uc_weather;
        private UC_Ship m_uc_ship;

        private int m_maxClients = 6;

        public Controller(MainWindow _view)
        {
            m_model = new DataModel();
            m_view = _view;

            Status.Init(m_view.Lbl_Status);

            m_uc_scenario = new UC_Scenario(this);
            m_uc_client = new UC_Client(this);
            m_uc_weather = new UC_Weather(this);
            m_uc_ship = new UC_Ship(this);
        }

        #region ---TabControl---

        public void ShowScenarioControl()
        {
            m_view.Cnvs_MainView.Children.Clear();

            m_view.Cnvs_MainView.Children.Add(m_uc_scenario);
        }

        public void ShowClientSettings()
        {
            m_view.Cnvs_MainView.Children.Clear();

            m_view.Cnvs_MainView.Children.Add(m_uc_client);
        }

        public void ShowWeatherSettings()
        {
            m_view.Cnvs_MainView.Children.Clear();

            m_view.Cnvs_MainView.Children.Add(m_uc_weather);
        }

        public void ShowShipSettings()
        {
            m_view.Cnvs_MainView.Children.Clear();

            m_view.Cnvs_MainView.Children.Add(m_uc_ship);
        }

        #endregion

        public void AddClientWindow()
        {
            if (m_newClientWindow == null)
            {
                // Create a new instance of the window to be spawned
                m_newClientWindow = new W_AddNewClient(this);

                // Set the startup location of the window to center with respect to the owner
                m_newClientWindow.WindowStartupLocation = WindowStartupLocation.CenterOwner;

                // Set the owner of the window
                m_newClientWindow.Owner = Application.Current.MainWindow;

                // Show the window
                m_newClientWindow.Show();
            }
            else
            {
                m_newClientWindow.Activate();
            }
        }

        public void CloseAddClientWindow(Window _window)
        {
            _window.Close();
            m_newClientWindow = null;
        }

        public void CreateNewClientItem(string _ip, int _commandPort, int _dataPort, EClientType _clientType)
        {
            if (m_uc_client.Wrp_ClientList.Children.Count < m_maxClients)
            {
                int id = m_model.CreateClient(_ip, _commandPort, _dataPort, _clientType);

                UC_ClientListItem uc_ClientListItem = new UC_ClientListItem(this, id, _ip, _commandPort, _dataPort, _clientType);
                m_uc_client.Wrp_ClientList.Children.Add(uc_ClientListItem);

                AddClientNode(id, _clientType);
            }
            else
            {
                MessageBox.Show("Maximum number of Clients exceeded!", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        public void ChangeClient(int _id)
        {
            Client client = m_model.Clients[_id - 1];

            if (m_newClientWindow == null)
            {
                // Create a new instance of the window to be spawned
                m_newClientWindow = new W_AddNewClient(this, client, true);

                // Set the startup location of the window to center with respect to the owner
                m_newClientWindow.WindowStartupLocation = WindowStartupLocation.CenterOwner;

                // Set the owner of the window
                m_newClientWindow.Owner = Application.Current.MainWindow;

                // Show the window
                m_newClientWindow.Show();
            }
            else
            {
                m_newClientWindow.Activate();
            }
        }

        public void AddClientNode(int _id, EClientType _clientType)
        {
            UC_ClientNode clientNode = new(this, _id, _clientType);
            m_uc_scenario.Wrp_ClientNodes.Children.Add(clientNode);
        }

        public void OverrideClient(Client _client)
        {
            m_model.OverrideClient(_client);

            m_uc_client.Wrp_ClientList.Children.RemoveAt(_client.ID - 1);
            UC_ClientListItem uc_ClientListItem = new UC_ClientListItem(this, _client.ID, _client.IP, _client.ClientCommandPort, _client.ClientDataPort, _client.ClientType);

            m_uc_client.Wrp_ClientList.Children.Insert(_client.ID - 1, uc_ClientListItem);

            OverrideClientNode(_client.ID - 1, _client.ClientType);
        }

        public void OverrideClientNode(int _id, EClientType _clientType)
        {
            m_uc_scenario.Wrp_ClientNodes.Children.RemoveAt(_id);
            UC_ClientNode clientNode = new UC_ClientNode(this, _id + 1, _clientType);

            m_uc_scenario.Wrp_ClientNodes.Children.Insert(_id, clientNode);
        }

        public void GetServerPorts(int _serverDataPort, int _serverCommandPort)
        {
            m_model.GetServerPorts(_serverDataPort, _serverCommandPort);
        }

        public void GetWeatherAndTimeSetting(EWeatherSetting _weather, int _time)
        {
            m_model.GetWeatherAndTimeSetting(_weather, _time);
        }

        public void SaveConfiguration()
        {
            m_model.SaveConfigToJson(jsonPath);
        }
    }
}
