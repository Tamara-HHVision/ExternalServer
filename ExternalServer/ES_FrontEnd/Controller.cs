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

        private UC_Scenario uc_scenario;
        private UC_Client uc_client;
        private UC_Weather uc_weather;
        private UC_Ship uc_ship;

        public Controller(MainWindow _view)
        {
            m_model = new DataModel();
            m_view = _view;

            uc_scenario = new UC_Scenario(this);
            uc_client = new UC_Client(this);
            uc_weather = new UC_Weather(this);
            uc_ship = new UC_Ship(this);
        }

        #region ---TabControl---

        public void ShowScenarioControl()
        {
            m_view.Cnvs_MainView.Children.Clear();

            m_view.Cnvs_MainView.Children.Add(uc_scenario);
        }

        public void ShowClientSettings()
        {
            m_view.Cnvs_MainView.Children.Clear();

            m_view.Cnvs_MainView.Children.Add(uc_client);
        }

        public void ShowWeatherSettings()
        {
            m_view.Cnvs_MainView.Children.Clear();

            m_view.Cnvs_MainView.Children.Add(uc_weather);
        }

        public void ShowShipSettings()
        {
            m_view.Cnvs_MainView.Children.Clear();

            m_view.Cnvs_MainView.Children.Add(uc_ship);
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

        public void CreateNewClient(string _ip, int _commandPort, int _dataPort, EClientType _clientType)
        {
            int maxClients = 6;
            UC_ClientListItem uc_ClientListItem = new UC_ClientListItem(_ip, _commandPort, _dataPort, _clientType);

            if (uc_client.Wrp_ClientList.Children.Count < maxClients)
                uc_client.Wrp_ClientList.Children.Add(uc_ClientListItem);
            else
                MessageBox.Show("Maximum number of Clients exceeded!", "Error", MessageBoxButton.OK, MessageBoxImage.Error);

            m_model.CreateClient(_ip, _commandPort, _dataPort, _clientType);
        }

        public void GetServerPorts(int _serverDataPort, int _serverCommandPort)
        {
            m_model.GetServerPorts(_serverDataPort, _serverCommandPort);
        }

        public void SaveConfiguration()
        {
            m_model.SaveConfigToJson(jsonPath);
        }
    }
}
