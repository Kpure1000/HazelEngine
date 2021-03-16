#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace hazel
{
	class Math
	{
	public:
		static float SmoothDamp(float current, float target,
			float& velocity, float smoothTime,
			float maxSpeed, float deltaTime);

		static glm::vec3 SmoothDamp(const glm::vec3& current, const glm::vec3& target,
			glm::vec3& velocity, float smoothTime,
			const glm::vec3& maxSpeed, float deltaTime);

		const static float Pi;
	};
}