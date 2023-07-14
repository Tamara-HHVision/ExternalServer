#pragma once

#include "cim_pch.h"
#include "NetworkPackets/UnrealCommandPackets.h"
#include "Clients/UnrealClientBase.h"
#include "NetworkUtilities/NetworkPacketUtils.h"


namespace CIM_Backend
{
	enum class ECommandType : uint8_t;

	class UnrealClientBase;

	/// <summary>
	/// Class sends Control commands to Unreal instances
	/// </summary>
	class UnrealCommandServer
	{
	private:

		int m_port;

		SOCKET m_commandSocket;
		sockaddr_in m_commandSocketAddress;

		std::map<int, SOCKET> m_commandListeners;


	public:

		UnrealCommandServer(int _port);


	private:

		void CreateCommandSocket();
		void WaitForCallBack(SOCKET socketToWaitFor);

	public:

		bool SendSetUpToClients();
		bool NotifyAllClientsOfStart();

		void SendSleepCommandToAll();


	private:

		void SendWorldConfigurationToClient(const std::unique_ptr<UnrealClientBase>& _client);
		void SendClientConfigurationToClient(const std::unique_ptr<UnrealClientBase>& _client);
		void SendStartCommandToClient(const std::unique_ptr<UnrealClientBase>& _client);
		void SendSleepCommandToClient(const std::unique_ptr<UnrealClientBase>& _client);


		template <typename T>
		void SendCommand(const std::unique_ptr<UnrealClientBase>& _targetClient, ECommandType _commandType, T& _msg)
		{
			char buffer[sizeof(CommandHeaderPacket) + sizeof(T)];
			CommandHeaderPacket header{ 0, 1, static_cast<uint8_t>(_commandType), _targetClient->GetConfiguration().id };
			NetworkPacketUtils::SerializePacket(header, _msg, buffer);

			Log::LogInfoToFile("Sending {}", sizeof(buffer));
			_targetClient->SendCommand(buffer);
		}

		void SendCommand(const std::unique_ptr<UnrealClientBase>& _targetClient, ECommandType _commandType);


	public:

		void ShutdownCommandServer();
		~UnrealCommandServer();
	};
}