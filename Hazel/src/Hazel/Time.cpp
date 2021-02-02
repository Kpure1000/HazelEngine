#include "hzpch.h"

#include "Time.h"
namespace hazel
{
	clock_t Time::programStart_time = 0;
	clock_t Time::frameStart_time = 0;
	clock_t Time::delta_time = 0;
}