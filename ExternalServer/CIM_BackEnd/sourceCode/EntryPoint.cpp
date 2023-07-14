#include "cim_pch.h"
#include "ServerInstance.h"


#define External _declspec(dllexport)

extern "C"
{
	External void SetUpBackEnd()
	{
		CIM_Backend::ServerInstance::sGetInstance().SetUpInstance();
	}
}


extern "C"
{
	External bool LoadConfiguration(const char* _path)
	{
		if (!CIM_Backend::ServerInstance::sGetInstance().LoadConfiguration(_path))
		{
			CIM_Backend::Log::LogErrorToFile("Configuration couldn't be loaded!");
			return false;
		}
		CIM_Backend::Log::LogInfoToFile("Configuration loaded succesfully");
		return true;
	};
}


extern "C"
{
	External void StartUnrealLoop()
	{
		CIM_Backend::Log::LogInfoToFile("Scenario loop is starting...");
		CIM_Backend::ServerInstance::sGetInstance().StartUnrealLoop();
		CIM_Backend::Log::LogInfoToFile("Scenario loop started!");
	};
}


extern "C"
{
	External void StopUnrealLoop()
	{
		CIM_Backend::ServerInstance::sGetInstance().StopUnrealLoop();
		CIM_Backend::Log::LogInfoToFile("Scenrario loop stopped!");
	}
}


extern "C"
{
	External void ShutDownBackend() {
		CIM_Backend::ServerInstance::sGetInstance().ShutdownInstance();
	};
}



extern "C"
{
	External void UpdateEgoCarClient(int _ID, bool _useLidar, bool _useRadar,
		bool _simulateRadarFalseNegative, bool _simulateRadarFalsePositives) 
	{
		CIM_Backend::Log::LogInfoToFile("ID {0} , Lidar {1}, Radar {2}", _ID, _useLidar, _useRadar);
	};
}