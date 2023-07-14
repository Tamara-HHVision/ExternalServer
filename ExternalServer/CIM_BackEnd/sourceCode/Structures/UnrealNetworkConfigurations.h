#pragma once
#include "cim_pch.h"
#include "ClientEnumeration.h"

namespace CIM_Backend
{
	struct ClientNetworkConfiguration
	{
		std::string ip;
		int clientDataPort;
		int clientCommandPort;
	};
	struct IClientConfiguration
	{
		uint8_t id;
		EClientType type;
		ClientNetworkConfiguration networkConfiguration;

		IClientConfiguration(int id, EClientType type, ClientNetworkConfiguration networkConfiguration)
			:id(id), type(type), networkConfiguration(networkConfiguration)
		{
		};

		virtual ~IClientConfiguration() = default;
	};



	struct EgoVehicleCameraOrigin
	{
		UnrealTypesEmulator::Vector3D cameraPosition;
		float cameraTilt;
	};
	struct EgoVehicleRadarFlags
	{
		bool useLidarModel;
		bool useRadarModel;
		bool useRadarFalseNegatives;
		bool useRadarFalsePositives;
	};

	struct EgoVehicleConfiguration :IClientConfiguration
	{
		const EgoVehicleCameraOrigin cameraOrigin;
		const EgoVehicleRadarFlags radarFlags;

		EgoVehicleConfiguration(int id, EClientType type, ClientNetworkConfiguration networkConfiguration, EgoVehicleCameraOrigin cameraOrigin, EgoVehicleRadarFlags radarFlags)
			: IClientConfiguration(id, type, networkConfiguration), cameraOrigin(cameraOrigin), radarFlags(radarFlags)
		{
		};
	};
	struct HQClientConfiguration : IClientConfiguration
	{
		HQClientConfiguration(int id, EClientType type, ClientNetworkConfiguration networkConfiguration)
			: IClientConfiguration(id, type, networkConfiguration)
		{
		};
	};
	struct PedestrianConfiguration :IClientConfiguration
	{
		PedestrianConfiguration(int id, EClientType type, ClientNetworkConfiguration networkConfiguration)
			: IClientConfiguration(id, type, networkConfiguration)
		{
		};
	};

	struct ObserverConfiguration : IClientConfiguration
	{
		const bool useVR;
		ObserverConfiguration(int id, EClientType type, ClientNetworkConfiguration networkConfiguration, bool useVR)
			: IClientConfiguration(id, type, networkConfiguration), useVR(useVR)
		{
		};
	};


	struct MocapConfiguration :IClientConfiguration
	{
		const std::string moCapServerIP;
		const std::string moCapClientIP;
		const bool useVR;
		const ECharacterSelection characterSelection;

		MocapConfiguration(int id, EClientType type, ClientNetworkConfiguration networkConfiguration, std::string mocapServerIP, std::string mocapClientIP, bool useVR, ECharacterSelection characterSelection)
			: IClientConfiguration(id, type, networkConfiguration), moCapServerIP(mocapServerIP), moCapClientIP(mocapClientIP), useVR(useVR), characterSelection(characterSelection)
		{
		};
	};

	struct VRConfiguration : IClientConfiguration
	{
		VRConfiguration(int id, EClientType type, ClientNetworkConfiguration networkConfiguration)
			: IClientConfiguration(id, type, networkConfiguration)
		{

		};
	};

	struct OpenScenarioConfiguration : IClientConfiguration
	{
		const std::string openScenarioSIP;
		const std::string openScenarioCIP;

		OpenScenarioConfiguration(int id, EClientType type, ClientNetworkConfiguration networkConfiguration, std::string openScnearioSIP, std::string openScnearioCIP)
			: IClientConfiguration(id, type, networkConfiguration), openScenarioSIP(openScenarioSIP), openScenarioCIP(openScenarioCIP)
		{
		};
	};
}
