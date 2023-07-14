#pragma once
#include "cim_pch.h"
#include "nlohmann/json.hpp"
#include "Structures/UnrealNetworkConfigurations.h"


namespace CIM_Backend
{
	enum class EWeatherSettings : uint8_t;
	
	/// <summary>
	/// This class loads or reloads the instance configuration 
	/// </summary>
	class ConfigurationLoader
	{

	private:

		EWeatherSettings m_weather;
		int m_maxPlayers = 0;
		int m_serverDataPort = 0;
		int m_serverCommandPort = 0;
		int m_serverAdminPort = 0;
		int m_time = 1200;
		bool m_configurationLoaded = false;

		std::vector<IClientConfiguration*> m_clientConfigurations;


	public:
		EWeatherSettings GetCurrentWeather() const { return m_weather; }
		int  GetMaxPlayerNumber() const { return m_maxPlayers; }
		int  GetServerDataPort() const { return m_serverDataPort; }
		int  GetServerCommandPort() const { return m_serverCommandPort; }
		int  GetServerAdminPort() const { return m_serverAdminPort; }
		int GetTime() const { return m_time; }

		const std::vector<IClientConfiguration*>& GetClientConfigurations() const { return m_clientConfigurations; }


	public:

		/// <summary>
		/// Loads or reloads config json
		/// </summary>
		/// <param name="fileLocation"></param>
		/// <returns></returns>
		bool LoadConfig(std::string_view fileLocation);

		
	private:

		void LoadWorldConfig(nlohmann::json& config);
		void LoadClientsConfig(nlohmann::json& config);

		void ClearConfiguration();

		template<typename T>
		T TryParseParameter(nlohmann::json node, const std::string& parameterName, bool(*checkFunction)(nlohmann::json node, const std::string& parameterName))
		{

			if (!(node.contains(parameterName) && checkFunction(node, parameterName)))
			{
				throw std::invalid_argument("Error property '" + parameterName + "'was not found or is not a valid type");
			}
			T nodeValue = node[parameterName];
			return nodeValue;
		}


		static bool CheckIfInt(const nlohmann::json node, const std::string& parameterName);
		static bool CheckIfBool(const nlohmann::json node, const std::string& parameterName);
		static bool CheckIfFloat(const nlohmann::json node, const std::string& parameterName);
		static bool CheckIfString(const nlohmann::json node, const std::string& parameterName);


	public:
		~ConfigurationLoader();
	};
}