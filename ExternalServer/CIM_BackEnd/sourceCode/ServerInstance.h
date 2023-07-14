#pragma once
#include "cim_pch.h"
#include <unordered_map>


namespace CIM_Backend
{
	class UnrealClientBase;
	class ConfigurationLoader;
	class UnrealDataServer;
	class UnrealCommandServer;

	class ServerInstance
	{
		
	public:

		std::unique_ptr<ConfigurationLoader> m_InstanceConfiguration;
		std::unique_ptr<UnrealDataServer> m_UnrealDataServer;
		std::unique_ptr<UnrealCommandServer> m_UnrealCommandServer;
		std::vector< std::unique_ptr<UnrealClientBase>> m_Clients;


	private:

		std::thread m_mainThread;
		bool m_isInstanceRunning = true;
		bool m_isServerSpawned = false;


	public:

		static ServerInstance& sGetInstance()
		{
			static ServerInstance s_Instance;
			return s_Instance;
		}


	public:

		void SetUpInstance();
		
		/// <summary>
		/// Creates clients from config.json file
		/// </summary>
		void SetUpClientsFromConfig();
		
		/// <summary>
		/// Loads config.json file
		/// </summary>
		/// <param name="path">file path to file: </param>
		bool LoadConfiguration(std::string_view _path);

		void ShutdownInstance();
		void StartUnrealLoop();
		void StopUnrealLoop();


	private:

		void StartWinsock();
		void SpawnServers();
		void SpawnPresetClientsFromConfig();


	private:

		ServerInstance();
		~ServerInstance();
		ServerInstance(const ServerInstance&) = delete;
		ServerInstance& operator=(const ServerInstance&) = delete;

	};
}