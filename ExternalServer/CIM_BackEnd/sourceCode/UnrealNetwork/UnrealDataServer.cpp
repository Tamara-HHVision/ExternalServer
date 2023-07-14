#include "cim_pch.h"

#include "UnrealDataServer.h"
#include "ServerInstance.h"
#include "Clients/UnrealClientBase.h"
#include "NetworkPackets/UnrealDataPackets.h"
#include "Enumerations/UnrealDataPacketTypes.h"


CIM_Backend::UnrealDataServer::UnrealDataServer(int _port, int _maxPlayersNumber)
	:m_port(_port), m_maxPlayer(_maxPlayersNumber)
{
	CreateTCPListenerSocket();
	CreateUDPListenerSocket();

	FD_ZERO(&m_masterSocket);
	FD_SET(m_tcpListenerSocket, &m_masterSocket);
}

void CIM_Backend::UnrealDataServer::StartServer()
{
	if (!m_isInitialized)
	{
		Log::LogInfoToFile("Start Server!");
		m_isListening = true;
		m_tcpListenerThread = std::thread(&UnrealDataServer::ListenForTCP, this);
		m_udpListenerThread = std::thread(&UnrealDataServer::ListenForUDP, this);
		m_isInitialized = true;
	};
	m_isPaused = false;
}

void CIM_Backend::UnrealDataServer::StopServer()
{
	m_isPaused = true;
	Log::LogInfoToFile("DataServer paused!");
}

void CIM_Backend::UnrealDataServer::CreateTCPListenerSocket()
{
	//create socket and check if valid
	m_tcpListenerSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_tcpListenerSocket == INVALID_SOCKET)
	{
		ShutdownServer();
		Log::LogErrorToFile("TCP Socket Error {}", WSAGetLastError());
	}

	m_serverTCPHint.sin_family = AF_INET;
	m_serverTCPHint.sin_port = htons(m_port);
	m_serverTCPHint.sin_addr.S_un.S_addr = INADDR_ANY;

	//Bind udp listener socket
	if (bind(m_tcpListenerSocket, (sockaddr*)&m_serverTCPHint, sizeof(m_serverTCPHint)) == SOCKET_ERROR)
	{
		ShutdownServer();
		Log::LogErrorToFile("TCP Socket Error {}", WSAGetLastError());
	}

	//start listening
	listen(m_tcpListenerSocket, SOMAXCONN);
}

void CIM_Backend::UnrealDataServer::CreateUDPListenerSocket()
{
	//Create socket and check if valid
	m_udpListenerSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (m_udpListenerSocket == INVALID_SOCKET)
	{
		ShutdownServer();
		Log::LogErrorToFile("Can't create UDP socket! Error {}", WSAGetLastError());

	}

	//Create server UDP hint structure
	m_serverUDPHint.sin_family = AF_INET;
	m_serverUDPHint.sin_port = htons(m_port);
	m_serverUDPHint.sin_addr.S_un.S_addr = INADDR_ANY;

	//Bind udp listener socket
	if (bind(m_udpListenerSocket, (sockaddr*)&m_serverUDPHint, sizeof(m_serverUDPHint)) == SOCKET_ERROR)
	{
		ShutdownServer();
		Log::LogErrorToFile("UDP Socket Error {}", WSAGetLastError());
	}
}

void CIM_Backend::UnrealDataServer::ListenForConnection()
{
	while (m_isListening)
	{
		SOCKET clientSocket;
		sockaddr_in clientAdress;
		socklen_t len = sizeof(sockaddr_in);
		clientSocket = accept(m_tcpListenerSocket, (sockaddr*)&clientAdress, &len);


		CIM_Backend::Log::LogInfoToFile("Connection accepted");
		CIM_Backend::Log::LogInfoToFile("new port {0}", ntohs(clientAdress.sin_port));
		for (const auto& client : ServerInstance::sGetInstance().m_Clients)
		{
			CIM_Backend::Log::LogInfoToFile("existing ports {0}", ntohs(client->m_dataAddress.sin_port));
			if ((client->m_dataAddress.sin_port == clientAdress.sin_port))
			{
				CIM_Backend::Log::LogInfoToFile("Found Client Address");
			}
		}
	}
}

void CIM_Backend::UnrealDataServer::ListenForTCP()
{
	using namespace std::literals::chrono_literals;

	while (m_isListening)
	{
		std::cout << std::to_string(m_isListening) + "\n";
		Log::LogInfoToFile("Server is listening!");

		fd_set copy = m_masterSocket;
		int socketCount = select(0, &copy, nullptr, nullptr, nullptr);

		// iterate through all sockets
		for (int i = 0; i < socketCount; i++)
		{
			SOCKET sock = copy.fd_array[i];

			if (sock == m_tcpListenerSocket && m_clientMap.size() <= m_maxPlayer)
			{

				//accept new connection
				SOCKET clientSocket;
				sockaddr_in clientAddress;
				socklen_t len = sizeof(sockaddr_in);
				clientSocket = accept(m_tcpListenerSocket, (sockaddr*)&clientAddress, &len);
				Log::LogInfoToFile("Server accepted!");

				bool mapContains = false;
				for (const auto& [client_id, socket] : m_clientMap)
				{
					if (socket == clientSocket)
					{
						mapContains = true;
					}
				}

				if (!mapContains)
				{
					if (clientSocket != SOCKET_ERROR)
					{
						// Add new connection to the list of connected clients
						FD_SET(clientSocket, &m_masterSocket);
						m_clientMap.emplace(m_lastClientID, clientSocket);
						m_lastClientID++;

						CIM_Backend::Log::LogInfoToFile("New member with ID {0} added!", m_lastClientID - 1);
					}
				}
			}
			else
			{
				char completePacket[1024];
				ZeroMemory(completePacket, 1024);

				int bytesIn = recv(sock, completePacket, sizeof(completePacket), 0);

				if (bytesIn <= 0)
				{
					// Drop the client
					closesocket(sock);
					FD_CLR(sock, &m_masterSocket);

					for (const auto& [client_id, socket] : m_clientMap)
					{
						if (socket == sock)
						{
							//handle quit client in server
							std::cout << "Client with ID " + std::to_string(client_id) + "Dissconnected! \n";
							m_clientMap.erase(client_id);

							break;
						}
					}
				}

				if (bytesIn == SOCKET_ERROR)
				{
					CIM_Backend::Log::LogErrorToFile("Error in receiving TCP data!");
					break;
				}
				if (bytesIn > 0)
				{
					CIM_Backend::Log::LogInfoToFile("TCP data in");
					HandleTCPData(sock, completePacket);
				}
			}
		}
	}

	CIM_Backend::Log::LogInfoToFile("TCP data listener was shutdown successfully!");
}

void CIM_Backend::UnrealDataServer::ListenForUDP()
{
	sockaddr_in client;
	int clientLength = sizeof(client);

	char packet[1024];
	
	while (m_isListening)
	{
		while(m_isPaused) {}

		ZeroMemory(&client, clientLength);
		ZeroMemory(packet, 1024);

		int bytesIn = recvfrom(m_udpListenerSocket, packet, sizeof(packet), 0, (sockaddr*)&client, &clientLength);
		if (bytesIn == SOCKET_ERROR)
		{
			CIM_Backend::Log::LogWarningToFile("Error receiving UDP");
		}
		else if (bytesIn > 0)
		{
			HandleUDPData(packet);
		}
	}
	std::cout << "Shutdown UDP!\n";
}


#pragma region --- TCP Functions ---

void CIM_Backend::UnrealDataServer::SendTCP(uint8_t _clientID, EServerPacketType _type)
{
	char buffer[sizeof(HeaderDataPacket)];
	HeaderDataPacket header{ g_PacketVersion, static_cast<uint8_t>(_type), _clientID };
	NetworkPacketUtils::SerializePacket(header, buffer);

	SendTCP(_clientID, buffer);
}

void CIM_Backend::UnrealDataServer::SendTCP(uint8_t _clientID, char* _packet)
{
	for (const auto& client : ServerInstance::sGetInstance().m_Clients)
	{
		if (client->GetConfiguration().id == _clientID)
		{
			int sendResult = send(client->m_dataSocket, _packet, 1024, 0);
			if (sendResult == SOCKET_ERROR)
			{
				CIM_Backend::Log::LogErrorToFile("Sending message failed: {0}", WSAGetLastError());
				return;
			}
		}
	}
}

void CIM_Backend::UnrealDataServer::SendTCPtoAll(EServerPacketType _type, uint8_t _targetClient)
{
	char buffer[sizeof(HeaderDataPacket)];
	HeaderDataPacket header{ g_PacketVersion, static_cast<uint8_t>(_type), _targetClient };
	NetworkPacketUtils::SerializePacket(header, buffer);

	SendTCPtoAll(buffer);
}

void CIM_Backend::UnrealDataServer::SendTCPtoAll(char* _packet)
{
	for (const auto& client : ServerInstance::sGetInstance().m_Clients)
	{
		int sendResult = send(client->m_dataSocket, _packet, 1024, 0);
		if (sendResult == SOCKET_ERROR)
		{
			CIM_Backend::Log::LogErrorToFile("Sending message failed: {0}", WSAGetLastError());
			return;
		}
	}
}

void CIM_Backend::UnrealDataServer::SendTCPtoAllExcept(uint8_t _clientID, EServerPacketType _type)
{
	char buffer[sizeof(HeaderDataPacket)];
	HeaderDataPacket header{ g_PacketVersion, static_cast<uint8_t>(_type), _clientID };
	NetworkPacketUtils::SerializePacket(header, buffer);

	SendTCPtoAllExcept(_clientID, buffer);
}

void CIM_Backend::UnrealDataServer::SendTCPtoAllExcept(uint8_t _clientID, char* _packet)
{
	for (const auto& client : ServerInstance::sGetInstance().m_Clients)
	{
		if (client->GetConfiguration().id != _clientID)
		{
			int sendResult = send(client->m_dataSocket, _packet, 1024, 0);
			if (sendResult == SOCKET_ERROR)
			{
				CIM_Backend::Log::LogErrorToFile("Sending message failed: {0}", WSAGetLastError());
				return;
			}
		}
	}
}

#pragma endregion

#pragma region --- UDP Functions ---

void CIM_Backend::UnrealDataServer::SendUDP(uint8_t _clientID, EServerPacketType _type)
{
	char buffer[sizeof(HeaderDataPacket)];
	HeaderDataPacket header{ g_PacketVersion, static_cast<uint8_t>(_type), _clientID };
	NetworkPacketUtils::SerializePacket(header, buffer);

	SendUDP(_clientID, buffer);
}

void CIM_Backend::UnrealDataServer::SendUDP(uint8_t _clientID, char* _packet)
{
	for (const auto& client : ServerInstance::sGetInstance().m_Clients)
	{
		if (client->GetConfiguration().id == _clientID)
		{
			int sendResult = sendto(m_udpListenerSocket, _packet, 1024, 0, (sockaddr*)&client->m_dataAddress, sizeof(client->m_dataAddress));
			if (sendResult == SOCKET_ERROR)
			{
				CIM_Backend::Log::LogErrorToFile("Sending Message Failed: {0}", WSAGetLastError());
				return;
			}
		}
	}
}

void CIM_Backend::UnrealDataServer::SendUDPtoAll(EServerPacketType _type, uint8_t _targetClient)
{
	char buffer[sizeof(HeaderDataPacket)];
	HeaderDataPacket header{ g_PacketVersion, static_cast<uint8_t>(_type), _targetClient };
	NetworkPacketUtils::SerializePacket(header, buffer);

	SendUDPtoAll(buffer);
}

void CIM_Backend::UnrealDataServer::SendUDPtoAll(char* _packet)
{
	for (const auto& client : ServerInstance::sGetInstance().m_Clients)
	{
		int sendResult = sendto(m_udpListenerSocket, _packet, 1024, 0, (sockaddr*)&client->m_dataAddress, sizeof(client->m_dataAddress));
		if (sendResult == SOCKET_ERROR)
		{
			CIM_Backend::Log::LogErrorToFile("Sending Message Failed: {0}", WSAGetLastError());
			return;
		}
	}
}

void CIM_Backend::UnrealDataServer::SendUDPtoAllExcept(uint8_t _clientID, EServerPacketType _type)
{
	char buffer[sizeof(HeaderDataPacket)];
	HeaderDataPacket header{ g_PacketVersion, static_cast<uint8_t>(_type), _clientID };
	NetworkPacketUtils::SerializePacket(header, buffer);
	SendUDPtoAllExcept(_clientID, buffer);
}

void CIM_Backend::UnrealDataServer::SendUDPtoAllExcept(uint8_t _clientID, char* _packet)
{
	for (const auto& client : ServerInstance::sGetInstance().m_Clients)
	{
		if (client->GetConfiguration().id != _clientID)
		{
			int sendResult = sendto(m_udpListenerSocket, _packet, 1024, 0, (sockaddr*)&client->m_dataAddress, sizeof(client->m_dataAddress));
			if (sendResult == SOCKET_ERROR)
			{
				CIM_Backend::Log::LogErrorToFile("Sending Message Failed: {0}", WSAGetLastError());
				return;
			}
		}
	}
}

#pragma endregion

#pragma region --- Client Messages ---

void CIM_Backend::UnrealDataServer::SendWelcomeToClient(int _clientID)
{
	SendTCP(_clientID, EServerPacketType::ServerWelcomePacket);
	UpdateNewClient(_clientID);
}

void CIM_Backend::UnrealDataServer::UpdateNewClient(int _clientID)
{
	for (const auto& client : ServerInstance::sGetInstance().m_Clients)
	{
		IClientConfiguration& config = client->GetConfiguration();
		if (config.id != _clientID)
		{
			SpawnNewMember mainStruct{ static_cast<uint8_t>(config.type), config.id };
			SendTCP(_clientID, EServerPacketType::NotifyOfNewMember, mainStruct);
		}
	}
}

void CIM_Backend::UnrealDataServer::NotifyClientsOfNewMember(uint8_t _type, int _id)
{
	SpawnNewMember mainStruct{ _type, _id };
	SendTCPtoAllExcept(_id, EServerPacketType::NotifyOfNewMember, mainStruct);
}

void CIM_Backend::UnrealDataServer::SendIndividualSpawnCommand(uint8_t _toClient, EClientType _type, uint8_t _newClientID)
{
	SpawnNewMember mainStruct{ static_cast<uint8_t>(_type), _newClientID };
	SendTCPtoAllExcept(_newClientID, EServerPacketType::NotifyOfNewMember, mainStruct);
}

void CIM_Backend::UnrealDataServer::NotifyClientsOfQuitting(uint8_t _client)
{
	SendTCPtoAll(EServerPacketType::NotifyOfQuit, _client);
}

void CIM_Backend::UnrealDataServer::NotifyClientsOfServerShutdown()
{
	SendTCPtoAll(EServerPacketType::ShutdownNotification);
}

#pragma endregion


void CIM_Backend::UnrealDataServer::HandleTCPData(SOCKET& _socket, char* _packet)
{
	HeaderDataPacket header;
	NetworkPacketUtils::DeserializePacket(header, _packet);

	switch (static_cast<EClientPacketType>(header.type))
	{
		case EClientPacketType::ClientWelcomePacket:
		{
			ReceiveWelcome(header.id, _socket, _packet);
		}
		break;
		default:
			break;
	}
}

void CIM_Backend::UnrealDataServer::HandleUDPData(char* _packet)
{
	HeaderDataPacket header;
	NetworkPacketUtils::DeserializePacket(header, _packet);

	switch (static_cast<EClientPacketType>(header.type))
	{
		case EClientPacketType::EgoTransform:
		{
			ReceiveVehicleTransform(header.id, _packet);
		}
		break;
		case EClientPacketType::PedestrinTransform:
		{
			ReceivePedestrianTransform(header.id, _packet);
		}
		break;
		case EClientPacketType::PedestrianAnimation:
		{
			ReceivePedestrianAnimation(header.id, _packet);
		}
		break;
		case EClientPacketType::MocapBoneData:
		{
			ReceiveMocapBoneData(header.id, _packet);
		}
		break;
		case EClientPacketType::VRTransform:
		{
			ReceiveVRTransform(header.id, _packet);
		}
		break;
		default:
			break;
	}
}

void CIM_Backend::UnrealDataServer::ReceiveWelcome(uint8_t _fromClientID, SOCKET& _socket, char* _packet)
{
	ClientWelcomePacket packetStruct;
	int offset = sizeof(HeaderDataPacket);
	NetworkPacketUtils::DeserializePacket(packetStruct, _packet, &offset);

	bool preconfiguredClient = false;
	for (const auto& client : ServerInstance::sGetInstance().m_Clients)
	{
		if (client->GetConfiguration().id == _fromClientID)
		{
			preconfiguredClient = true;
			client->m_dataSocket = _socket;
		}
	}
	if (!preconfiguredClient)
	{

	}
	SendWelcomeToClient(_fromClientID);
}

void CIM_Backend::UnrealDataServer::ReceivePedestrianTransform(uint8_t _fromClientID, char* _packet)
{
	PedestrianTransformPacket packetStruct;
	int offset = sizeof(HeaderDataPacket);
	NetworkPacketUtils::DeserializePacket(packetStruct, _packet, &offset);

	SendUDPtoAllExcept(_fromClientID, EServerPacketType::PedestrianTransformUpdate, packetStruct);
}

void CIM_Backend::UnrealDataServer::ReceivePedestrianAnimation(uint8_t _fromClientID, char* _packet)
{
	PedestrianAnimationPacket packetStruct;
	int offset = sizeof(HeaderDataPacket);

	NetworkPacketUtils::DeserializePacket(packetStruct, _packet, &offset);

	SendUDPtoAllExcept(_fromClientID, EServerPacketType::PedestrianAnimationUpdate, packetStruct);
}

void CIM_Backend::UnrealDataServer::ReceiveVRTransform(uint8_t _fromClientID, char* _packet)
{
	VR_ClientTransformPacket packetStruct;
	int offset = sizeof(HeaderDataPacket);

	NetworkPacketUtils::DeserializePacket(packetStruct, _packet, &offset);

	SendUDPtoAllExcept(_fromClientID, EServerPacketType::VRTransformUpdate, packetStruct);
}

void CIM_Backend::UnrealDataServer::ReceiveVehicleTransform(uint8_t _fromClientID, char* _packet)
{
	EgoCarTransformPacket packetStruct;
	int offset = sizeof(HeaderDataPacket);

	NetworkPacketUtils::DeserializePacket(packetStruct, _packet, &offset);

	SendUDPtoAllExcept(_fromClientID, EServerPacketType::EgoTransformUpdate, packetStruct);
}

void CIM_Backend::UnrealDataServer::ReceiveMocapBoneData(uint8_t _fromClientID, char* _packet)
{
	MocapFrame packetStruct;
	int offset = sizeof(HeaderDataPacket);

	packetStruct.Deserialize(_packet, &offset);

	char buffer[(sizeof(HeaderDataPacket) + (sizeof(MoCapBonePacket) * 21))];

	packetStruct.Deserialize(_packet, &offset);

	HeaderDataPacket header{ g_PacketVersion,  static_cast<uint8_t>(EServerPacketType::MocapBoneDataUpdate), _fromClientID };
	NetworkPacketUtils::SerializePacket(header, buffer);

	offset = sizeof(HeaderDataPacket);

	packetStruct.Serialize(buffer, &offset);

	SendUDPtoAllExcept(_fromClientID, buffer);
}

void CIM_Backend::UnrealDataServer::ReceiveTrafficCarSpawn(uint8_t _fromClientID, char* _packet)
{
	TrafficCarSpawnPacket packetStruct;
	int offset = sizeof(HeaderDataPacket);

	NetworkPacketUtils::DeserializePacket(packetStruct, _packet, &offset);
}

void CIM_Backend::UnrealDataServer::ReceiveTrafficCarData(uint8_t _fromClient, char* _packet)
{
	TrafficCarDataPacket packetStruct;
	int offset = sizeof(HeaderDataPacket);

	NetworkPacketUtils::DeserializePacket(packetStruct, _packet, &offset);
}

void CIM_Backend::UnrealDataServer::ShutdownServer()
{
	if (m_tcpListenerSocket)
	{
		closesocket(m_tcpListenerSocket);
	}
	if (m_udpListenerSocket)
	{
		closesocket(m_udpListenerSocket);
	}
	for (const auto& [client_id, socket] : m_clientMap)//Loop through All Connected Clients
	{
		closesocket(socket);
	}

	m_isListening = false;
	if (m_tcpListenerThread.joinable())
	{
		m_tcpListenerThread.join();
	}
	if (m_udpListenerThread.joinable())
	{
		m_udpListenerThread.join();
	}
}


CIM_Backend::UnrealDataServer::~UnrealDataServer()
{
	ShutdownServer();
}