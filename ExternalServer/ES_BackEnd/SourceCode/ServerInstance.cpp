#include "ServerInstance.h"

void ES_BackEnd::ServerInstance::Logger()
{
	// Create a logger instance with a specific name
	auto logger = spdlog::basic_logger_mt("my_logger", "log_file.txt");

	logger->info("This is an informational message");
	logger->error("An error occurred");

}
