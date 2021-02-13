#include "hzpch.h"
#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace hazel
{

	Ref<spdlog::logger> Log::m_CoreLogger;

	Ref<spdlog::logger> Log::m_ClientLogger;
	
	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		m_CoreLogger = spdlog::stderr_color_mt("HAZEL");
		m_CoreLogger->set_level(spdlog::level::trace);
		
		m_ClientLogger= spdlog::stderr_color_mt("APP");
		m_ClientLogger->set_level(spdlog::level::trace);
	}

}
