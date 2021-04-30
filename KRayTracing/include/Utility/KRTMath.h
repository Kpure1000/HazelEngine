#pragma once

#include "../Core/Core.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace krt {

	class KRT_API KRTMath {
	public:
		static double Drand48();

		static  void Srand48(unsigned int i);

		static glm::vec3 RandomUnitSphere();

		static glm::vec2 RandomUnitDisk();

	private:
		static unsigned long long seed;

	};

}