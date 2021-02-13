#pragma once

#include<ctime>

#include "Hazel/Core/Core.h"

namespace hazel
{
	class HAZEL_API Time
	{
	public:

		inline static float currentTime()
		{
			return static_cast<float>(clock() - programStart_time) / 1000.0f; 
		}

		inline static float deltaTime()
		{
			return static_cast<float>(delta_time) / 1000.0f;
		}

		inline static void Begin()
		{
			programStart_time = clock();
		}

		inline static void Update()
		{
			delta_time = clock() - frameStart_time;
			frameStart_time = clock();
		}

	private:

		static clock_t programStart_time;

		static clock_t frameStart_time;

		static clock_t delta_time;
	};

}