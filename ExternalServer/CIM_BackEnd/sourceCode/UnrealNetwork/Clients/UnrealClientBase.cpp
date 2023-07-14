#include "cim_pch.h"
#include "UnrealClientBase.h"
#include "Structures/UnrealNetworkConfigurations.h"


CIM_Backend::UnrealClientBase::UnrealClientBase(IClientConfiguration* _configuration, SOCKET _socket, sockaddr_in _address)
	: m_configuration(_configuration)
{
	m_addressSize = sizeof(m_dataAddress);
}

CIM_Backend::UnrealClientBase::UnrealClientBase(IClientConfiguration* _configuration)
	:m_configuration(_configuration)
{
	CreateDataSocket(m_configuration->networkConfiguration.ip, m_configuration->networkConfiguration.clientDataPort);
	CreateCommandListenerSocket(m_configuration->networkConfiguration.ip, m_configuration->networkConfiguration.clientCommandPort);
	ConnectToCommandListenerSocket();
}

void CIM_Backend::UnrealClientBase::UpdateClientConfiguration(IClientConfiguration& _configuration)
{
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(_configuration.networkConfiguration.clientCommandPort);
	inet_pton(AF_INET, _configuration.networkConfiguration.ip.c_str(), &(address.sin_addr));
	
	if ((m_commandListenerAddress.sin_addr.S_un.S_addr == address.sin_addr.S_un.S_addr)
		&& (m_commandListenerAddress.sin_port == address.sin_port))
	{
		
	}
}

void CIM_Backend::UnrealClientBase::CreateCommandListenerSocket(const std::string& _ip, int _port)
{
	m_commandListenerAddress.sin_family = AF_INET;
	m_commandListenerAddress.sin_port = htons(_port);
	inet_pton(AF_INET, _ip.c_str(), &(m_commandListenerAddress.sin_addr));

	m_commandListenerSocket = socket(AF_INET, SOCK_STREAM, 0);
}

void CIM_Backend::UnrealClientBase::CreateDataSocket(const std::string& _ip, int _port)
{
	m_dataAddress.sin_family = AF_INET;
	m_dataAddress.sin_port = htons(_port);
	inet_pton(AF_INET, _ip.c_str(), &(m_dataAddress.sin_addr));

	m_dataSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_dataSocket == INVALID_SOCKET)
	{
		CIM_Backend::Log::LogErrorToFile("Data socket is invalid!");
		return;
	}
	CIM_Backend::Log::LogInfoToFile("Data socket created!");
}

void CIM_Backend::UnrealClientBase::ConnectToCommandListenerSocket()
{
	int connectionResult = connect(m_commandListenerSocket, (sockaddr*)&m_commandListenerAddress, sizeof(m_commandListenerAddress));
	if (connectionResult == SOCKET_ERROR)
	{
		std::cout << "Failed to connect to clients listener" + std::to_string(WSAGetLastError()) + "\n";
		closesocket(m_commandListenerSocket);
	}
	std::cout << "Connected! \n";
}

void CIM_Backend::UnrealClientBase::SendUDPToThisClient(const SOCKET& _senderSocket, char* _packet)
{
	int sendResult = sendto(_senderSocket, _packet, 1024, 0, (sockaddr*)&m_dataAddress, m_addressSize);
	[[unlikely]] if (sendResult == SOCKET_ERROR)
	{
		std::cout << "Sending UDP message failed! " + std::to_string(WSAGetLastError()) + "\n";
	}
}

void CIM_Backend::UnrealClientBase::SendTCPToThisClient(const SOCKET& _senderSocket, char* _packet)
{
	int sendResult = send(_senderSocket, _packet, 1024, 0);
	[[unlikely]] if (sendResult == SOCKET_ERROR)
	{
		std::cout << "Sending TCP message failed! " + std::to_string(WSAGetLastError()) + "\n";
	}
}

void CIM_Backend::UnrealClientBase::SendCommand(char* _packet)
{
	std::cout << sizeof(_packet);

	int sendResult = send(m_commandListenerSocket, _packet, 256, 0);
	[[unlikely]] if (sendResult == SOCKET_ERROR)
	{
		std::cout << "Sending command message failed! " + std::to_string(WSAGetLastError()) + "\n";
	}
}

CIM_Backend::UnrealClientBase::~UnrealClientBase()
{
	closesocket(m_dataSocket);
}