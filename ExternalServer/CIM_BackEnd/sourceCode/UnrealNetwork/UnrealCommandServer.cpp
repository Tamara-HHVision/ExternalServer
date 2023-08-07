#include "cim_pch.h"
#include "UnrealCommandServer.h"
#include "ServerInstance.h"
#include "ConfigParser/ConfigurationLoader.h"
#include "Clients/EgoVehicleClient.h"
#include "Clients/MotionCaptureClient.h"
#include "Clients/OpenScenarioClient.h"

CIM_Backend::UnrealCommandServer::UnrealCommandServer(int _port) : m_port(_port)
{
	CreateCommandSocket();
}

void CIM_Backend::UnrealCommandServer::CreateCommandSocket()
{
	m_commandSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_commandSocket == INVALID_SOCKET)
	{
		throw std::runtime_error("Can't create command socket! Error " + std::to_string(WSAGetLastError()));
	}

	m_commandSocketAddress.sin_family = AF_INET;
	m_commandSocketAddress.sin_port = htons(m_port);
	m_commandSocketAddress.sin_addr.S_un.S_addr = INADDR_ANY;

	if (bind(m_commandSocket, (sockaddr*)&m_commandSocketAddress, sizeof(m_commandSocketAddress)) == SOCKET_ERROR)
	{
		ShutdownCommandServer();
		throw std::runtime_error("Socket Error: " + std::to_string(WSAGetLastError()));
	}

	//Start Listening
	listen(m_commandSocket, SOMAXCONN);
}

void CIM_Backend::UnrealCommandServer::WaitForCallBack(SOCKET socketToWaitFor)
{
	char callBackPacket[4];
	int callBackPackettSize = sizeof(callBackPacket);
	int bytesIn = recv(socketToWaitFor, callBackPacket, callBackPackettSize, 0);
	std::cout << "received callback \n";
}

bool CIM_Backend::UnrealCommandServer::SendSetUpToClients()
{
	for (const auto& client : ServerInstance::sGetInstance().m_Clients)
	{
		Log::LogInfoToFile("IP {} ", client->GetConfiguration().networkConfiguration.ip);
		Log::LogInfoToFile("Command port {} ", client->GetConfiguration().networkConfiguration.clientCommandPort);
		Log::LogInfoToFile("Data port {} ", client->GetConfiguration().networkConfiguration.clientDataPort);
		Log::LogInfoToFile("Client: {} ", client->GetConfiguration().type);
		SendWorldConfigurationToClient(client);
		SendClientConfigurationToClient(client);
	}
	return true;
}

bool CIM_Backend::UnrealCommandServer::NotifyAllClientsOfStart()
{
	for (auto const& client : ServerInstance::sGetInstance().m_Clients)
	{
		SendStartCommandToClient(client);
	}
	return true;
}

void CIM_Backend::UnrealCommandServer::SendSleepCommandToAll()
{
	for (auto const& client : ServerInstance::sGetInstance().m_Clients)
	{
		SendSleepCommandToClient(client);
	}
}

void CIM_Backend::UnrealCommandServer::SendWorldConfigurationToClient(const std::unique_ptr<UnrealClientBase>& _client)
{
	WorldConfigurationPacket packet
	{
		m_port,
		ServerInstance::sGetInstance().m_InstanceConfiguration->GetServerDataPort(),
		ServerInstance::sGetInstance().m_InstanceConfiguration->GetTime(),
		static_cast<int>(ServerInstance::sGetInstance().m_InstanceConfiguration->GetCurrentWeather())
	};
	
	SendCommand(_client, ECommandType::WorldConfiguration, packet);
}

void CIM_Backend::UnrealCommandServer::SendClientConfigurationToClient(const std::unique_ptr<UnrealClientBase>& _client)
{
	ClientConfigurationPacket baseClientPacket
	{
		_client->GetConfiguration().id,
		_client->GetConfiguration().networkConfiguration.clientDataPort,
		static_cast<uint8_t>(_client->GetConfiguration().type)
	};

	switch (_client->GetConfiguration().type)
	{
		case EClientType::EgoVehicle:
		{
			EgoVehicleClient* egoClient = static_cast<EgoVehicleClient*>(_client.get());

			EgoCarConfigurationPacket egoPacket{
				baseClientPacket,
				egoClient->GetConfiguration().cameraOrigin,
				egoClient->GetConfiguration().radarFlags
			};

			SendCommand(_client, ECommandType::ClientConfiguration, egoPacket);
			return;
		}
		break;
		case EClientType::HQClient:
		{
			SendCommand(_client, ECommandType::ClientConfiguration, baseClientPacket);
			return;
		}
		break;
		case EClientType::Pedestrian:
		{
			SendCommand(_client, ECommandType::ClientConfiguration, baseClientPacket);
			return;
		}
		break;
		case EClientType::ControlCenter:
		{
			SendCommand(_client, ECommandType::ClientConfiguration, baseClientPacket);
			return;
		}
		case EClientType::MotionCapture:
		{
			MotionCaptureClient* moCapClient = static_cast<MotionCaptureClient*>(_client.get());

			uint32_t serverIP, clientIP;

			inet_pton(AF_INET, moCapClient->GetConfiguration().moCapServerIP.c_str(), &serverIP);
			serverIP = ntohl(serverIP);

			inet_pton(AF_INET, moCapClient->GetConfiguration().moCapClientIP.c_str(), &clientIP);
			clientIP = ntohl(clientIP);

			bool isVR;
			
			MoCapConfigurationPacket moCapPacket;
			moCapPacket.clientConfig = baseClientPacket;
			moCapPacket.serverIp = serverIP;
			moCapPacket.clientIp = clientIP;
			moCapPacket.characterName = static_cast<uint8_t>(moCapClient->GetConfiguration().characterSelection);
			moCapPacket.isVR = static_cast<bool>(moCapClient->GetConfiguration().useVR);



			Log::LogInfoToFile("Client Ip and int {}", clientIP);
			Log::LogInfoToFile(moCapClient->GetConfiguration().moCapClientIP.c_str());
			Log::LogInfoToFile("Client Ip and int {}", serverIP);
			Log::LogInfoToFile(moCapClient->GetConfiguration().moCapServerIP.c_str());

			SendCommand(_client, ECommandType::ClientConfiguration, moCapPacket);
			return;
		}
		break;
		case EClientType::VR:
		{
			SendCommand(_client, ECommandType::ClientConfiguration, baseClientPacket);
			return;
		}
		break;
		case EClientType::OpenScenario:
		{
			OpenScenarioClient* openScenarioClient = static_cast<OpenScenarioClient*>(_client.get());

			uint32_t serverIP, clientIP;

			inet_pton(AF_INET, openScenarioClient->GetConfiguration().openScenarioSIP.c_str(), &serverIP);
			serverIP = ntohl(serverIP);

			inet_pton(AF_INET, openScenarioClient->GetConfiguration().openScenarioCIP.c_str(), &clientIP);
			clientIP = ntohl(clientIP);

			OpenScenarioConfigurationPacket openScenarioPacket;
			openScenarioPacket.clientConfig = baseClientPacket;
			openScenarioPacket.serverIP = serverIP;
			openScenarioPacket.clientIP = clientIP;


			Log::LogInfoToFile("Client Ip and int {}", clientIP);
			Log::LogInfoToFile(openScenarioClient->GetConfiguration().openScenarioCIP.c_str());
			Log::LogInfoToFile("Client Ip and int {}", serverIP);
			Log::LogInfoToFile(openScenarioClient->GetConfiguration().openScenarioSIP.c_str());

			
			SendCommand(_client, ECommandType::ClientConfiguration, openScenarioPacket);
			return;
		}
		break;
		default:
			break;
	}
}

void CIM_Backend::UnrealCommandServer::SendStartCommandToClient(const std::unique_ptr<UnrealClientBase>& _client)
{
	SendCommand(_client, ECommandType::StartClient);
}

void CIM_Backend::UnrealCommandServer::SendSleepCommandToClient(const std::unique_ptr<UnrealClientBase>& _client)
{
	SendCommand(_client, ECommandType::StopClient);
}


void CIM_Backend::UnrealCommandServer::SendCommand(const std::unique_ptr<UnrealClientBase>& _targetClient, ECommandType _commandType)
{
	char buffer[sizeof(CommandHeaderPacket)];
	CommandHeaderPacket header{ 0, 1, static_cast<uint8_t>(_commandType), _targetClient->GetConfiguration().id };
	Log::LogInfoToFile("Client ID: {} ", _targetClient->GetConfiguration().id);
	NetworkPacketUtils::SerializePacket(header, buffer);

	_targetClient->SendCommand(buffer);
}

void CIM_Backend::UnrealCommandServer::ShutdownCommandServer()
{
	closesocket(m_commandSocket);
}

CIM_Backend::UnrealCommandServer::~UnrealCommandServer()
{
	ShutdownCommandServer();
}