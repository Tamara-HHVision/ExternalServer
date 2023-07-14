#pragma once
#include "cim_pch.h"

#pragma warning(push,0),
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#pragma warning(pop)


namespace CIM_Backend
{
	class Log
	{
	private:
		static std::shared_ptr<spdlog::logger> m_infoLogger;
		static std::shared_ptr<spdlog::logger> m_errorLogger;
		static std::shared_ptr<spdlog::logger> m_warningLogger;

	public:
		
		static void Init();

		template <typename T, typename... Args>
		inline static void LogInfoToFile(const T& msg, Args &&...args)
		{
			GetInfoLogger()->info(msg, std::forward<Args>(args)...);
		}

		template <typename T, typename... Args>
		inline static void LogWarningToFile(const T& msg, Args &&...args)
		{
			GetWarningLogger()->info(msg, std::forward<Args>(args)...);
		}

		template <typename T, typename... Args>
		inline static void LogErrorToFile(const T& msg, Args &&...args)
		{
			GetErrorLogger()->info(msg, std::forward<Args>(args)...);
		}


		inline static std::shared_ptr<spdlog::logger>& GetInfoLogger() {return m_infoLogger;}
		inline static std::shared_ptr<spdlog::logger>& GetErrorLogger() {return m_errorLogger;}
		inline static std::shared_ptr<spdlog::logger>& GetWarningLogger() {return m_warningLogger;}

	
	};
}

