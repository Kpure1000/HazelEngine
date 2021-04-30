#include "krtpch.h"

#include "../../include/Utility/KRTMath.h"

#ifndef RAND_M
#define RAND_M 0x100000000LL  
#endif // !RAND_M
#ifndef RAND_C
#define RAND_C 0xB16  
#endif // !RAND_C
#ifndef RAND_A
#define RAND_A 0x5DEECE66DLL 
#endif // !RAND_A

namespace krt {

	unsigned long long KRTMath::seed = 1;

	double KRTMath::Drand48()
	{
		seed = (RAND_A * seed + RAND_C) & 0xffffffffffffLL;
		unsigned int x = seed >> 16;
		return  ((double)x / (double)RAND_M);
	}

	void KRTMath::Srand48(unsigned int i)
	{
		srand(i);
		seed = (((long long int)i) << 16) | rand();
	}

	glm::vec3 KRTMath::RandomUnitSphere()
	{
		glm::vec3 re;
		do
		{
			re = 2.0f * glm::vec3(Drand48(), Drand48(), Drand48()) - glm::vec3(1.0f);
		} while (re.length() > 1.0f);
		return re;
	}

	glm::vec2 KRTMath::RandomUnitDisk()
	{
		glm::vec2 p;
		do
		{
			p = 2.0f * glm::vec2(Drand48(), Drand48()) - glm::vec2(1, 1);
		} while (glm::dot(p, p) >= 1.0f);
		return p;
	}

}