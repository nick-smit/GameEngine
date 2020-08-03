#include "pch.h"
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Engine {
	std::shared_ptr<spdlog::logger> Logger::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Logger::s_ClientLogger;

	bool Logger::Init()
	{
		Logger::s_CoreLogger = spdlog::stdout_color_mt("ENGINE");
		Logger::s_CoreLogger->set_level(spdlog::level::debug);

		Logger::s_ClientLogger = spdlog::stdout_color_mt("APP");
		Logger::s_ClientLogger->set_level(spdlog::level::debug);

		return true;
	}

	void Logger::Shutdown()
	{
		Logger::s_ClientLogger = nullptr;
		Logger::s_CoreLogger = nullptr;
	}
}

