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

		inline static Ref<spdlog::logger>& GetCoreLogger()
		{
			return m_CoreLogger;
		}

		inline static Ref<spdlog::logger>& GetClientLogger()
		{
			return m_ClientLogger;
		}

	public:

		// --Core Log----------------------------------------

		template<typename... T>
		inline static void TraceCore(T... args) { m_CoreLogger->trace(args...); }

		template<typename... T>
		inline static void InfoCore(T... args) { m_CoreLogger->info(args...); }

		template<typename... T>
		inline static void WarnCore(T... args) { m_CoreLogger->warn(args...); }

		template<typename... T>
		inline static void ErrorCore(T... args) { m_CoreLogger->error(args...); }

		template<typename... T>
		static void AssertCore(int assert, T... args)
		{
#ifdef HZ_ENABLE_ASSERT
			if (!assert) { ErrorCore(args...); __debugbreak(); }
#endif // HZ_ENABLE_ASSERT
		}

		template<typename... T>
		inline static void CriticalCore(T... args) { m_CoreLogger->critical(args...); }

		template<typename... T>
		inline static void DebugCore(T... args) 
		{ 
#ifdef HZ_DEBUG
			m_CoreLogger->debug(args...); 
#endif // HZ_DEBUG
		}

		// --Client Log----------------------------------------

		template<typename... T>
		inline static void Trace(T... args) { m_ClientLogger->trace(args...); }

		template<typename... T>
		inline static void Info(T... args) { m_ClientLogger->info(args...); }

		template<typename... T>
		inline static void Warn(T... args) { m_ClientLogger->warn(args...); }

		template<typename... T>
		inline static void Error(T... args) { m_ClientLogger->error(args...); }

		template<typename... T>
		inline static void Assert(int assert, T... args)
		{
#ifdef HZ_ENABLE_ASSERT
			if (!assert) { Error(args...); __debugbreak(); }
#endif // HZ_ENABLE_ASSERT
		}

		template<typename... T>
		inline static void Critical(T... args) { m_ClientLogger->critical(args...); }

		template<typename... T>
		inline static void Debug(T... args) 
		{
#ifdef HZ_DEBUG
			m_ClientLogger->debug(args...); 
#endif // HZ_DEBUG
		}

	private:

		/// <summary>
		/// Core Logger
		/// </summary>
		static Ref<spdlog::logger> m_CoreLogger;

		/// <summary>
		/// Client Logger
		/// </summary>
		static Ref<spdlog::logger> m_ClientLogger;

	};


}
