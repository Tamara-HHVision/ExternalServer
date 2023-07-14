#pragma once
#include "cim_pch.h"
#include "ClientEnumeration.h"
#include "Structures/UnrealNetworkConfigurations.h"

struct ClientNetworkConfiguration;

namespace CIM_Backend
{
	/// <summary>
	/// Base class to represent a connected client
	/// </summary>
	class UnrealClientBase
	{
	public: 

		SOCKET m_commandListenerSocket;					// Socket that the Client runs on
		sockaddr_in m_commandListenerAddress;

		SOCKET m_dataSocket;						   // Socket that the Client sends data to the server
		sockaddr_in m_dataAddress;

		std::thread m_clientListenerThread;


	protected:

		std::unique_ptr<IClientConfiguration> m_configuration;


	private:

		int m_addressSize;


	public:

		UnrealClientBase(IClientConfiguration* _configuration, SOCKET _socket, sockaddr_in _address);
		UnrealClientBase(IClientConfiguration* _configuration);

		inline IClientConfiguration& GetConfiguration() const { return *m_configuration; }

		/// <summary>
		/// Resets the current config to a new one
		/// </summary>
		/// <param name="_configuration">new config</param>
		void UpdateClientConfiguration(IClientConfiguration& _configuration);


	private: 

		void CreateCommandListenerSocket(const std::string& _ip, int _port);
		void CreateDataSocket(const std::string& _ip, int _port);


	public:

		void ConnectToCommandListenerSocket();

		void SendUDPToThisClient(const SOCKET& _senderSocket, char* _packet);
		void SendTCPToThisClient(const SOCKET& _senderSocket, char* _packet);
		void SendCommand(char* _packet);


	public:

		virtual ~UnrealClientBase();
	};
}