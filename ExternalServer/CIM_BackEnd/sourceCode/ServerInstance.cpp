#include "cim_pch.h"
#include "ServerInstance.h"

#include "UnrealNetwork/UnrealDataServer.h"
#include "ConfigParser/ConfigurationLoader.h"
#include "UnrealNetwork/Clients/PedestrianClient.h"
#include "UnrealNetwork/Clients/EgoVehicleClient.h"
#include "UnrealNetwork/Clients/HQClient.h"
#include "UnrealNetwork/Clients/MotionCaptureClient.h"
#include "UnrealNetwork/Clients/ObserverClient.h"
#include "UnrealNetwork/Clients/VRClient.h"
#include "UnrealNetwork/Clients/OpenScenarioClient.h"
#include "UnrealNetwork/UnrealCommandServer.h"

void CIM_Backend::ServerInstance::SetUpInstance()
{
	CIM_Backend::Log::Init();
	StartWinsock();
	m_InstanceConfiguration = std::make_unique<ConfigurationLoader>();
	CIM_Backend::Log::LogInfoToFile("Backend Started!");
}

void CIM_Backend::ServerInstance::StartWinsock()
{
	WSAData wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsResult = WSAStartup(ver, &wsData);
	[[unlikely]] if (wsResult != 0)
	{
		WSACleanup();
		throw std::runtime_error("Can't start Winsock, Error " + std::to_string(WSAGetLastError()));
	}

	CIM_Backend::Log::LogInfoToFile("Winsock started successfully!");

}

void CIM_Backend::ServerInstance::SpawnServers()
{
	if (!m_isServerSpawned)
	{
		m_UnrealCommandServer = std::make_unique<UnrealCommandServer>(m_InstanceConfiguration->GetServerCommandPort());
		m_UnrealDataServer = std::make_unique<UnrealDataServer>(m_InstanceConfiguration->GetServerDataPort(), m_InstanceConfiguration->GetMaxPlayerNumber());
		m_isServerSpawned = true;
	}
	Log::LogInfoToFile("Server spawned!");
}

bool CIM_Backend::ServerInstance::LoadConfiguration(std::string_view _path)
{
	if (m_InstanceConfiguration->LoadConfig(_path))
	{
		Log::LogInfoToFile("Configuration loaded successfully!");
		SpawnServers();
		SetUpClientsFromConfig();
		Log::LogInfoToFile("Predefined clients were spawned!");
		return true;
	}
	else
	{
		return false;
	}
}



void CIM_Backend::ServerInstance::SpawnPresetClientsFromConfig()
{
	for (const auto& clientConfig : m_InstanceConfiguration->GetClientConfigurations())
	{
		bool clientExists = false;
		for (const auto& client : m_Clients)
		{
			clientExists = client->GetConfiguration().id == clientConfig->id;
			if (clientExists)
			{
				break;
			};
		}
		if (!clientExists)
		{
			Log::LogInfoToFile("Client of Type: {} about to spawn", clientConfig->type);
			switch (clientConfig->type)
			{
				case EClientType::EgoVehicle:
				{
					m_Clients.push_back(std::make_unique<EgoVehicleClient>((EgoVehicleConfiguration*)clientConfig));
				}
				break;
				case EClientType::HQClient:
				{
					m_Clients.push_back(std::make_unique<HQClient>((HQClientConfiguration*)clientConfig));
				}
				break;
				case EClientType::Pedestrian:
				{
					m_Clients.push_back(std::make_unique<PedestrianClient>((PedestrianConfiguration*)clientConfig));
				}
				break;
				case EClientType::MotionCapture:
				{
					m_Clients.push_back(std::make_unique<MotionCaptureClient>(static_cast<MocapConfiguration*>(clientConfig)));
				}
				break;
				case EClientType::Observer:
				{
					m_Clients.push_back(std::make_unique<ObserverClient>((ObserverConfiguration*)clientConfig));
				}
				break;
				case EClientType::VR:
				{
					m_Clients.push_back(std::make_unique<VRClient>((VRConfiguration*)clientConfig));
				}
				break;
				case EClientType::OpenScenario:
				{
					m_Clients.push_back(std::make_unique<OpenScenarioClient>((OpenScenarioConfiguration*)clientConfig));
				}
				break;
				default:
					break;
			}
		}
	}
}

void CIM_Backend::ServerInstance::SetUpClientsFromConfig()
{
	SpawnPresetClientsFromConfig();
	m_UnrealCommandServer->SendSetUpToClients();
}

void CIM_Backend::ServerInstance::StartUnrealLoop()
{
	m_UnrealCommandServer->NotifyAllClientsOfStart();
	m_UnrealDataServer->StartServer();
}

void CIM_Backend::ServerInstance::StopUnrealLoop()
{
	m_UnrealDataServer->StopServer();
}

void CIM_Backend::ServerInstance::ShutdownInstance()
{
	m_isInstanceRunning = false;
	m_UnrealCommandServer->SendSleepCommandToAll();
	m_Clients.clear();
}


CIM_Backend::ServerInstance::ServerInstance() {}
CIM_Backend::ServerInstance::~ServerInstance() 
{
	WSACleanup();
}