using System.Runtime.InteropServices;

namespace ES_FrontEnd
{
    class BackendInterface
    {
        //public const string cppBackEndDLL = "C:/Users/tamara.graovac/Projects/ExternalServer/ExternalServer/bin/x64/Debug/CIM_BackEnd.dll";
        public const string cppBackEndDLL = "CIM_BackEnd.dll";

        [DllImport(cppBackEndDLL, CallingConvention = CallingConvention.Cdecl, SetLastError = true)]
        public static extern void SetUpBackEnd();


        [DllImport(cppBackEndDLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern bool LoadConfiguration(string path);

        [DllImport(cppBackEndDLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern void StartUnrealLoop();


        [DllImport(cppBackEndDLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern void UpdateEgoCarClient(int ID, bool useLidar, bool useRadar,
        bool simulateRadarFalseNegative, bool simulateRadarFalsePositives);

        [DllImport(cppBackEndDLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ShutDownBackend();
    }
}
