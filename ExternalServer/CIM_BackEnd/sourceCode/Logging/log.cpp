#include "cim_pch.h"
#include "log.h"
#include "spdlog/sinks/stdout_color_sinks.h"



	std::shared_ptr<spdlog::logger> CIM_Backend::Log::m_infoLogger;
	std::shared_ptr<spdlog::logger> CIM_Backend::Log::m_warningLogger;
	std::shared_ptr<spdlog::logger> CIM_Backend::Log::m_errorLogger;
	
	
	void CIM_Backend::Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		try
		{
			m_errorLogger = spdlog::basic_logger_mt("ERROR", "logs/cimlog.txt");
			m_warningLogger = spdlog::basic_logger_mt("WARNING", "logs/cimlog.txt");
			m_infoLogger = spdlog::basic_logger_mt("INFO", "logs/cimlog.txt");
		}
		catch (const spdlog::spdlog_ex& ex)
		{
			std::cout << "Log init failed: " << ex.what() << std::endl;
		}

	}
