#pragma once

#include "Core/Core.h"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace hazel
{

	class HAZEL_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger()
		{
			return m_CoreLogger;
		}

		inline static std::shared_ptr<spdlog::logger>& GetClientLogger()
		{
			return m_ClientLogger;
		}

	private:

		/// <summary>
		/// Core Logger
		/// </summary>
		static std::shared_ptr<spdlog::logger> m_CoreLogger;

		/// <summary>
		/// Client Logger
		/// </summary>
		static std::shared_ptr<spdlog::logger> m_ClientLogger;

	};


}

#define HZ_CORE_TRACE(...)		 ::hazel::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define HZ_CORE_INFO(...)		 ::hazel::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HZ_CORE_WARN(...)		 ::hazel::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HZ_CORE_ERROR(...)		 ::hazel::Log::GetCoreLogger()->error(__VA_ARGS__)
#define HZ_CORE_CRITICAL(...)	 ::hazel::Log::GetCoreLogger()->critical(__VA_ARGS__)


#define HZ_CLIENT_TRACE(...)	 ::hazel::Log::GetClientLogger()->trace(__VA_ARGS__)
#define HZ_CLIENT_INFO(...)	     ::hazel::Log::GetClientLogger()->info(__VA_ARGS__)
#define HZ_CLIENT_WARN(...)		 ::hazel::Log::GetClientLogger()->warn(__VA_ARGS__)
#define HZ_CLIENT_ERROR(...)	 ::hazel::Log::GetClientLogger()->error(__VA_ARGS__)
#define HZ_CLIENT_CRITICAL(...)	 ::hazel::Log::GetClientLogger()->critical(__VA_ARGS__)
