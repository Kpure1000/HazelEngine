#pragma once

#include "Log.h"

#include <chrono>
#include <iostream>

namespace hazel
{
	class Timer
	{
	public:
		Timer(const char* name, const std::function<void(const char*, float)>& timerCallBack)
			:m_Name(name), isStoped(false), m_TimerCallBack(timerCallBack)
		{
			m_StartTimePoint = std::chrono::high_resolution_clock::now();
		}
		
		~Timer()
		{
			if (!isStoped)
				Stop();
		}

	private:
		void Stop()
		{
			auto endTimePoint = std::chrono::high_resolution_clock::now();

			auto start = std::chrono::time_point_cast
				<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch().count();
			auto end = std::chrono::time_point_cast
				<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();
			float result = (end - start) * 0.001f;
			
			isStoped = true;
			m_TimerCallBack(m_Name, result);
		}

	private:
		const char* m_Name;

		std::chrono::time_point<std::chrono::steady_clock> m_StartTimePoint;
		
		std::function<void(const char*,float)>m_TimerCallBack;

		bool isStoped;
	};
}