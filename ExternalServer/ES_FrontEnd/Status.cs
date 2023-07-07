using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Threading;

namespace ES_FrontEnd
{
    static class Status
    {
        private static Label s_Label;

        public static void Init(Label _label)
        {
            s_Label = _label;
        }

        public static void Log(string _message)
        {
            if (s_Label == null)
            {
                MessageBox.Show("Status Label or Popup was not assigned!", "Status", MessageBoxButton.OK, MessageBoxImage.Warning);
            }

            s_Label.Content = _message;
            s_Label.Visibility = Visibility.Visible;

            DispatcherTimer timer = new DispatcherTimer();

            // Duration of timer
            timer.Interval = TimeSpan.FromSeconds(3);
            timer.Tick += (sender, e) =>
            {
                s_Label.Visibility = Visibility.Hidden; s_Label.Content = _message;
                timer.Stop();
            };

            timer.Start();
        }
    }
}
