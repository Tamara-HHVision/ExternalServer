using System.Runtime.InteropServices;

namespace ES_FrontEnd
{
    class BackendInterface
    {
        [DllImport("ES_BackEnd")]
        public static extern int TestFunction();
    }
}
