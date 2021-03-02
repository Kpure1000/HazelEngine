#pragma once

#include <thread>
#include <mutex>
#include <fstream>

#include "Hazel/Core/Log.h"
#include "Hazel/Utility/ThreadPool.h"

namespace hazel
{
	using FloatingPointMiscroseconds = std::chrono::duration<double, std::micro>;

	struct ProfileResult
	{
		std::string name;

		FloatingPointMiscroseconds start;
		std::chrono::microseconds elapsedTime;
		std::thread::id threadID;
	};

	struct InstrumentationSession
	{
		std::string name;
	};

	class HAZEL_API InstrumentCache
	{
	public:
		InstrumentCache(const InstrumentCache&) = delete;

		InstrumentCache(InstrumentCache&&) = delete;

		bool Begin(const std::string filePath);

		void End();
		
		/// <summary>
		/// Push result into cache
		/// </summary>
		/// <param name="result"></param>
		void operator<<(const ProfileResult& result);

		void WriteFileHeader();

		void WriteFileFooter();

		static InstrumentCache& GetInstance()
		{
			static InstrumentCache instance;
			return instance;
		}

	private:
		InstrumentCache()
			:m_ThreadPool(4)
		{
		}
		
		void SaveProfile();

		static const size_t maxSize = 2048;
		static const size_t maxContainerSize = 8;

		size_t curResult = 0;
		size_t curContainer = 0;
		size_t savingContainer = 0;

		std::array<std::array<ProfileResult, maxSize>, maxContainerSize> m_Container;
		
		std::ofstream m_OutputStream;

		ThreadPool m_ThreadPool;
		
	};

	class HAZEL_API Instrumentor
	{
	public:
		Instrumentor(const Instrumentor&) = delete;

		Instrumentor(Instrumentor&&) = delete;

		/// <summary>
		/// Begin session
		/// </summary>
		/// <param name="name">Session name, from line or func</param>
		/// <param name="filePath"></param>
		void BeginSession(const std::string& name, const std::string& filePath = "results.json");

		/// <summary>
		/// End session
		/// </summary>
		void EndSession();

		/// <summary>
		/// Write profile
		/// </summary>
		/// <param name="result"></param>
		void WriteProfile(const ProfileResult& result);

		static Instrumentor& GetInstance()
		{
			static Instrumentor instance;
			return instance;
		}

	private:
		Instrumentor()
			:m_CurrentSession(nullptr)
		{}

		~Instrumentor()
		{
			EndSession();
		}

		void WriteHeader()
		{
			InstrumentCache::GetInstance().WriteFileHeader();
		}

		void WriteFooter()
		{
			InstrumentCache::GetInstance().WriteFileFooter();
		}

		void InternalEndSession();

	private:
		std::mutex m_Mutex;

		InstrumentationSession* m_CurrentSession;

		//std::ofstream m_OutputStream;
	};

	class HAZEL_API LogTimer
	{
	public:
		LogTimer(const char* name)
			:m_Name(name), isStoped(false)
		{
			m_StartTimePoint = std::chrono::high_resolution_clock::now();
		}

		~LogTimer()
		{
			if (!isStoped)
				Stop();
		}

	private:
		void Stop()
		{
			auto endTimePoint = std::chrono::high_resolution_clock::now();
			auto highResStart = FloatingPointMiscroseconds{ m_StartTimePoint.time_since_epoch() };
			auto elapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch()
				- std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch();

			Log::DebugCore("Func: {0}, DeltaTime: {1}us", m_Name, elapsedTime.count());

			isStoped = true;
		}

	private:
		const char* m_Name;

		std::chrono::time_point<std::chrono::steady_clock> m_StartTimePoint;

		bool isStoped;

	};

	class HAZEL_API InstrumentationTimer
	{
	public:
		InstrumentationTimer(const char* name)
			:m_Name(name), isStoped(false)
		{
			m_StartTimePoint = std::chrono::high_resolution_clock::now();
		}

		~InstrumentationTimer()
		{
			if (!isStoped)
				Stop();
		}

	private:
		void Stop()
		{
			auto endTimePoint = std::chrono::high_resolution_clock::now();
			auto highResStart = FloatingPointMiscroseconds{ m_StartTimePoint.time_since_epoch() };
			auto elapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch()
				- std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch();

			Instrumentor::GetInstance().WriteProfile({ m_Name, highResStart ,elapsedTime,std::this_thread::get_id() });

			isStoped = true;
		}

	private:
		const char* m_Name;

		std::chrono::time_point<std::chrono::steady_clock> m_StartTimePoint;

		bool isStoped;

	};

	namespace InstrumentorUtils {

		template <size_t N>
		struct ChangeResult
		{
			char Data[N];
		};

		template <size_t N, size_t K>
		constexpr auto CleanupOutputString(const char(&expr)[N], const char(&remove)[K])
		{
			ChangeResult<N> result = {};

			size_t srcIndex = 0;
			size_t dstIndex = 0;
			while (srcIndex < N)
			{
				size_t matchIndex = 0;
				while (matchIndex < K - 1 && srcIndex + matchIndex < N - 1 && expr[srcIndex + matchIndex] == remove[matchIndex])
					matchIndex++;
				
				if (matchIndex == K - 1)
					srcIndex += matchIndex;
				
				result.Data[dstIndex++] = expr[srcIndex] == '"' ? '\'' : expr[srcIndex];
				srcIndex++;
			}
			return result;
		}

	}

}

#if  defined(HZ_DEBUG) //|| defined(HZ_RELEASE)
#define HZ_PROFILE 1
#endif // HZ_DEBUG

#if HZ_PROFILE
	#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
		#define HZ_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__DMC__) && (__DMC__ >= 0x810)
		#define HZ_FUNC_SIG __PRETTY_FUNCTION__
	#elif (defined(__FUNCSIG__) || (_MSC_VER))
		#define HZ_FUNC_SIG __FUNCSIG__
	#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
		#define HZ_FUNC_SIG __FUNCTION__
	#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
		#define HZ_FUNC_SIG __FUNC__
	#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
		#define HZ_FUNC_SIG __func__
	#elif defined(__cplusplus) && (__cplusplus >= 201103)
		#define HZ_FUNC_SIG __func__
	#else
		#define HZ_FUNC_SIG "HZ_FUNC_SIG unknown!"
	#endif

	#define HZ_PROFILE_BEGIN_SESSION(name, filepath) hazel::Instrumentor::GetInstance().BeginSession(name, filepath)
	#define HZ_PROFILE_END_SESSION() hazel::Instrumentor::GetInstance().EndSession()
	#define HZ_PROFILE_SCOPE_LINE2(name, line) constexpr auto fixedName##line = hazel::InstrumentorUtils::CleanupOutputString(name, "__cdecl ");\
											   hazel::InstrumentationTimer timer##line(fixedName##line.Data)
	#define HZ_PROFILE_SCOPE_LINE(name, line) HZ_PROFILE_SCOPE_LINE2(name, line)
	#define HZ_PROFILE_SCOPE(name) HZ_PROFILE_SCOPE_LINE(name, __LINE__)
	#define HZ_PROFILE_FUNCTION() HZ_PROFILE_SCOPE(HZ_FUNC_SIG)
#else
	#define HZ_PROFILE_BEGIN_SESSION(name, filepath)
	#define HZ_PROFILE_END_SESSION()
	#define HZ_PROFILE_SCOPE(name)
	#define HZ_PROFILE_FUNCTION()
#endif // HZ_PROFILE
