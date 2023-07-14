#pragma once
#include "UnrealCommandPacketType.h"
#include "ClientEnumeration.h"
#include "MapEnumeration.h"
#include "Structures/UnrealNetworkConfigurations.h"

namespace CIM_Backend
{
	/// <summary>
	/// used to identify the incoming command packet
	/// </summary>
	struct CommandHeaderPacket
	{
		uint8_t ver_major = 0;
		uint8_t ver_minor = 1;

		uint8_t commandType;
		uint8_t targetClientID;
	};

	/// <summary>
	/// used to send base data which each client needs
	/// </summary>
	struct ClientConfigurationPacket
	{
		uint8_t assignedID;
		int clientPort;
		uint8_t type;
	};

	/// <summary>
	/// used to send config data which each main vehicle client needs (contains base data too)
	/// </summary>
	struct EgoCarConfigurationPacket
	{
		ClientConfigurationPacket clientConfig;
		EgoVehicleCameraOrigin cameraOrigin;
		EgoVehicleRadarFlags radarFlags;
	};

	/// <summary>
	/// used to send config data which each mocap client needs (contains base data too)
	/// </summary>
	struct MoCapConfigurationPacket 
	{
		ClientConfigurationPacket clientConfig;
		uint32_t serverIp;
		uint32_t clientIp;
		uint32_t characterName;
		bool isVR;
	};

	/// <summary>
	/// used to send config data which OpenScenario client needs (contains base data too)
	/// </summary>
	struct OpenScenarioConfigurationPacket
	{
		ClientConfigurationPacket clientConfig;
		uint32_t serverIP;
		uint32_t clientIP;
	};

	/// <summary>
	/// contains world/scene config data
	/// </summary>
	struct WorldConfigurationPacket
	{
		int serverCommandPort;
		int serverDataPort;
		int time;
		int weather;
	};
}