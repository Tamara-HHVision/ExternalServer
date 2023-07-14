#include "cim_pch.h"
#include "NetworkPackets/UnrealDataPackets.h"

namespace CIM_Backend
{
	class UnrealClientBase;

	/// <summary>
	/// Class handles all data exchnage with Unreal instances
	/// </summary>
	class UnrealDataServer 
	{
	private:

		bool m_isInitialized = false;
		bool m_isPaused = false;

		int m_port;
		int m_maxPlayer;

		SOCKET m_tcpListenerSocket;
		SOCKET m_udpListenerSocket;
		sockaddr_in m_serverTCPHint;
		sockaddr_in m_serverUDPHint;

		fd_set m_masterSocket;

		std::map<int, SOCKET> m_clientMap;

		HANDLE m_tcpThreadHandler;
		HANDLE m_udpThreadHandler;

		std::thread m_tcpListenerThread;
		std::thread m_connectionListenerThread;
		std::thread m_udpListenerThread;

		std::atomic<bool> m_isListening;

		int m_lastClientID = 1;


	public:

		UnrealDataServer(int _port, int _maxPlayersNumber);
		
		void StartServer();
		void StopServer();


	private:

		void CreateTCPListenerSocket();
		void CreateUDPListenerSocket();

		void ListenForConnection();
		void ListenForTCP();
		void ListenForUDP();

#pragma region --- TCP Sender Funktion ---

		template<typename T>
		void SendTCP(uint8_t _clientID, EServerPacketType _type, T& _msg)
		{
			char buffer[sizeof(HeaderDataPacket) + sizeof(T)];
			HeaderDataPacket header{ g_PacketVersion, static_cast<uint8_t>(_type), _clientID };

			NetworkPacketUtils::SerializePacket(header, _msg, buffer);
			SendTCP(_clientID, buffer);
		}
		void SendTCP(uint8_t _clientID, EServerPacketType _type);
		void SendTCP(uint8_t _clientID, char* _packet);


		template<typename T>
		void SendTCPtoAll(uint8_t _clientID, EServerPacketType _type, T& _msg)
		{
			char buffer[sizeof(HeaderDataPacket) + sizeof(T)];
			HeaderDataPacket header{ g_PacketVersion, static_cast<uint8_t>(_type),_clientID };

			NetworkPacketUtils::SerializePacket(header, _msg, buffer);
			SendTCPtoAll(buffer);
		}
		void SendTCPtoAll(EServerPacketType _type, uint8_t _targetClient = 0);
		void SendTCPtoAll(char* _packet);


		template<typename T>
		void SendTCPtoAllExcept(uint8_t _clientID, EServerPacketType _type, T& _msg)
		{
			char buffer[sizeof(HeaderDataPacket) + sizeof(T)];
			HeaderDataPacket header{ g_PacketVersion, static_cast<uint8_t>(_type),_clientID };

			NetworkPacketUtils::SerializePacket(header, _msg, buffer);
			SendTCPtoAllExcept(_clientID, buffer);
		}
		void SendTCPtoAllExcept(uint8_t _clientID, EServerPacketType _type);
		void SendTCPtoAllExcept(uint8_t _clientID, char* _packet);

#pragma endregion 


#pragma region --- UDP Sender Funktion ---

		template<typename T>
		void SendUDP(uint8_t _clientID, EServerPacketType _type, T& _msg)
		{
			char buffer[sizeof(HeaderDataPacket) + sizeof(T)];
			HeaderDataPacket header{ g_PacketVersion, static_cast<uint8_t>(_type),_clientID };

			NetworkPacketUtils::SerializePacket(header, _msg, buffer);
			SendUDP(_clientID, buffer);
		}
		void SendUDP(uint8_t _clientID, EServerPacketType _type);
		void SendUDP(uint8_t _clientID, char* _packet);


		template<typename T>
		void SendUDPtoAll(uint8_t _clientID, EServerPacketType _type, T& _msg)
		{
			char buffer[sizeof(HeaderDataPacket) + sizeof(T)];
			HeaderDataPacket header{ g_PacketVersion, static_cast<uint8_t>(_type),_clientID };

			NetworkPacketUtils::SerializePacket(header, _msg, buffer);
			SendUDPtoAll(buffer);
		}
		void SendUDPtoAll(EServerPacketType _type, uint8_t _targetClient = 0);
		void SendUDPtoAll(char* _packet);


		template<typename T>
		void SendUDPtoAllExcept(uint8_t _clientID, EServerPacketType _type, T& _msg)
		{
			char buffer[sizeof(HeaderDataPacket) + sizeof(T)];
			HeaderDataPacket header{ g_PacketVersion, static_cast<uint8_t>(_type),_clientID };

			NetworkPacketUtils::SerializePacket(header, _msg, buffer);
			SendUDPtoAllExcept(_clientID, buffer);
		}
		void SendUDPtoAllExcept(uint8_t _clientID, EServerPacketType _type);
		void SendUDPtoAllExcept(uint8_t _clientID, char* _packet);

#pragma endregion


		void SendWelcomeToClient(int _clientID);
		void UpdateNewClient(int _clientID);
		void NotifyClientsOfNewMember(uint8_t _type, int _id);
		void SendIndividualSpawnCommand(uint8_t _toClient, EClientType _type, uint8_t _newCLientID);
		void NotifyClientsOfQuitting(uint8_t _client);
		void NotifyClientsOfServerShutdown();


#pragma region --- Receive Messages ---

	private:

		void HandleTCPData(SOCKET& _socket, char* _packet);
		void HandleUDPData(char* _packet);
		void ReceiveWelcome(uint8_t _fromClientID, SOCKET& _socket, char* _packet);
		void ReceivePedestrianTransform(uint8_t _fromClientID, char* _packet);
		void ReceivePedestrianAnimation(uint8_t _fromClientID, char* _packet);
		void ReceiveVRTransform(uint8_t _fromClientID, char* _packet);
		void ReceiveVehicleTransform(uint8_t _fromClientID, char* _packet);
		void ReceiveMocapBoneData(uint8_t _fromClientID, char* _packet);
		void ReceiveTrafficCarSpawn(uint8_t _fromClient, char* _packet);
		void ReceiveTrafficCarData(uint8_t _fromClient, char* _packet);

#pragma endregion

public:
	
	void ShutdownServer();
	~UnrealDataServer();
	};
}