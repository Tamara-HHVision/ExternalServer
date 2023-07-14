#include "cim_pch.h"
#include "ConfigurationLoader.h"
#include "MapEnumeration.h"
#include <string_view>


bool CIM_Backend::ConfigurationLoader::LoadConfig(std::string_view fileLocation)
{
	std::ifstream fileStream(fileLocation.data());
	nlohmann::json jsonConfiguration = nlohmann::json::parse(fileStream);
	try
	{
		if (m_configurationLoaded)
		{
			ClearConfiguration();
			LoadWorldConfig(jsonConfiguration);
			LoadClientsConfig(jsonConfiguration);
		}
		else
		{
			LoadWorldConfig(jsonConfiguration);
			LoadClientsConfig(jsonConfiguration);
			m_configurationLoaded = true;
		}
	}
	catch (const std::exception& exception)
	{
		Log::LogInfoToFile(exception.what());
		return false;
	}
	return true;
}

void CIM_Backend::ConfigurationLoader::LoadWorldConfig(nlohmann::json& config)
{
	m_maxPlayers = TryParseParameter<int>(config, "maxClients", CheckIfInt);
	m_weather = static_cast<EWeatherSettings>(TryParseParameter<int>(config, "weatherSettings", CheckIfInt));
	m_serverDataPort = TryParseParameter<int>(config, "serverDataPort", CheckIfInt);
	m_serverCommandPort = TryParseParameter<int>(config, "serverCommandPort", CheckIfInt);
	m_time = TryParseParameter<int>(config, "time", CheckIfInt);
}

void CIM_Backend::ConfigurationLoader::LoadClientsConfig(nlohmann::json& config)
{
	m_clientConfigurations.reserve(config["clients"].size());

	for (auto const& clientNode : config["clients"])
	{
		int id = TryParseParameter<int>(clientNode, "id", CheckIfInt);
		EClientType type = static_cast<EClientType>(TryParseParameter<int>(clientNode, "type", CheckIfInt));

		ClientNetworkConfiguration networkConfiguration;
		networkConfiguration.ip = TryParseParameter<std::string>(clientNode, "ip", CheckIfString);
		networkConfiguration.clientDataPort = TryParseParameter<int>(clientNode, "dataPort", CheckIfInt);
		networkConfiguration.clientCommandPort = TryParseParameter<int>(clientNode, "commandPort", CheckIfInt);

		switch (type)
		{
		case EClientType::EgoVehicle:
		{
			float camX, camY, camZ;
			if (clientNode.contains("cameraPosition"))
			{
				auto const& camPosNode = clientNode["cameraPosition"];
				if (camPosNode.is_array() && camPosNode.size() == 3)
				{

					camX = (camPosNode[0].is_number_float() || camPosNode[0].is_number_integer()) ? (float)camPosNode[0] : 0;
					camY = (camPosNode[1].is_number_float() || camPosNode[1].is_number_integer()) ? (float)camPosNode[1] : 0;
					camZ = (camPosNode[2].is_number_float() || camPosNode[2].is_number_integer()) ? (float)camPosNode[2] : 0;

					if (camX == 0 || camY == 0 || camZ == 0)
					{
						std::cout << "WARNING! One of camera axis is either 0 or not a numeric type";
					}
				}
				else
				{
					return;
				}
			}
			else
			{
				throw std::invalid_argument("Error property cameraPosition was not found or is not a valid type");
			}
			EgoVehicleCameraOrigin egoVehicleCameraOrigin;
			egoVehicleCameraOrigin.cameraPosition = { camX,camY,camZ };
			egoVehicleCameraOrigin.cameraTilt = TryParseParameter<float>(clientNode, "cameraTilt", CheckIfFloat);;

			EgoVehicleRadarFlags egoVehicleRadarFlags;
			egoVehicleRadarFlags.useLidarModel = TryParseParameter<bool>(clientNode, "useLidarModel", CheckIfBool);
			egoVehicleRadarFlags.useRadarModel = TryParseParameter<bool>(clientNode, "useRadarModel", CheckIfBool);
			egoVehicleRadarFlags.useRadarFalseNegatives = TryParseParameter<bool>(clientNode, "useRadarFalseNegatives", CheckIfBool);
			egoVehicleRadarFlags.useRadarFalsePositives = TryParseParameter<bool>(clientNode, "useRadarFalsePositives", CheckIfBool);
			m_clientConfigurations.push_back(new EgoVehicleConfiguration(id, type,
				networkConfiguration, egoVehicleCameraOrigin, egoVehicleRadarFlags));
		}
		break;
		case EClientType::HQClient:
		{
			m_clientConfigurations.push_back(new HQClientConfiguration(id, type, networkConfiguration));
		}
		break;
		case EClientType::Pedestrian:
		{
			m_clientConfigurations.push_back(new PedestrianConfiguration(id, type, networkConfiguration));
		}
		break;
		case EClientType::Observer:
		{
			bool useVR = TryParseParameter<bool>(clientNode, "useVR", CheckIfBool);
			m_clientConfigurations.push_back(new ObserverConfiguration(id, type, networkConfiguration, useVR));
		}
		break;
		case EClientType::MotionCapture:
		{
			std::string moCapServerIP = TryParseParameter<std::string>(clientNode, "moCapServerIP", CheckIfString);
			std::string moCapClientIP = TryParseParameter<std::string>(clientNode, "moCapClientIP", CheckIfString);
			bool useVR = TryParseParameter<bool>(clientNode, "useVR", CheckIfBool);
			ECharacterSelection characterSelection = static_cast<ECharacterSelection>(TryParseParameter<int>(clientNode, "characterSelection", CheckIfInt));

			m_clientConfigurations.push_back(new MocapConfiguration(id, type, 
				networkConfiguration, moCapServerIP, moCapClientIP, useVR, characterSelection));
		}
		break;
		case EClientType::OpenScenario:
		{	std::string openScenarioSIP = TryParseParameter<std::string>(clientNode, "openScenarioServerIP", CheckIfString);
			std::string openScenarioCIP = TryParseParameter<std::string>(clientNode, "openScenarioClientIP", CheckIfString);

			m_clientConfigurations.push_back(new OpenScenarioConfiguration(id, type,
				networkConfiguration, openScenarioSIP, openScenarioCIP));
		}
		break;
		case EClientType::VR:
		{
			m_clientConfigurations.push_back(new VRConfiguration(id, type, networkConfiguration));
		}
		break;
		default:
			break;
		}
	}
}

void CIM_Backend::ConfigurationLoader::ClearConfiguration()
{
	m_clientConfigurations.clear();
}

bool CIM_Backend::ConfigurationLoader::CheckIfInt(const nlohmann::json node, const std::string& parameterName)
{
	return node[parameterName].is_number_integer();
}

bool CIM_Backend::ConfigurationLoader::CheckIfBool(const nlohmann::json node, const std::string& parameterName)
{
	return node[parameterName].is_boolean();
}

bool CIM_Backend::ConfigurationLoader::CheckIfFloat(const nlohmann::json node, const std::string& parameterName)
{
	return node[parameterName].is_number_float();
}

bool CIM_Backend::ConfigurationLoader::CheckIfString(const nlohmann::json node, const std::string& parameterName)
{
	return node[parameterName].is_string();
}

CIM_Backend::ConfigurationLoader::~ConfigurationLoader()
{
	ClearConfiguration();
}
