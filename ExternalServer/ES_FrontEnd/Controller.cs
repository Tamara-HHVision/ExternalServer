using ES_FrontEnd.UserControls;
using ES_FrontEnd.Windows;
using System.Windows;

namespace ES_FrontEnd
{
    public class Controller
    {
        private MainWindow m_view;
        private Model m_model;

        private W_AddNewClient? m_newClientWindow = null;


        public Controller(MainWindow _view)
        {
            m_model = new Model();
            m_view = _view;
        }

        #region ---TabControl---

        public void ShowScenarioControl()
        {
            m_view.Cnvs_MainView.Children.Clear();

            UC_Scenario uc_Scenario = new UC_Scenario(this);

            m_view.Cnvs_MainView.Children.Add(uc_Scenario);
        }

        public void ShowClientSettings()
        {
            m_view.Cnvs_MainView.Children.Clear();

            UC_Client uc_Client = new UC_Client(this);

            m_view.Cnvs_MainView.Children.Add(uc_Client);
        }

        public void ShowWeatherSettings()
        {
            m_view.Cnvs_MainView.Children.Clear();
            UC_Weather uc_weather = new UC_Weather(this);

            m_view.Cnvs_MainView.Children.Add(uc_weather);
        }

        public void ShowShipSettings()
        {
            m_view.Cnvs_MainView.Children.Clear();
            UC_Ship uc_Ship = new UC_Ship(this);
            m_view.Cnvs_MainView.Children.Add(uc_Ship);
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
    }
}
