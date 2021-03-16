#include "hzpch.h"

#include "Math.h"

#include "Hazel/Core/Time.h"

namespace hazel
{
	const float Math::Pi = glm::pi<float>();

	float Math::SmoothDamp(float current, float target,
		float& velocity, float smoothTime,
		float maxSpeed = FLT_MAX, float deltaTime = Time::deltaTime())
	{
		smoothTime = glm::max(0.0001f, smoothTime);
		float num = 2.0f / smoothTime;
		float num2 = num * deltaTime;
		float num3 = 1.0f / (1.0f + num2 + 0.48f * num2 * num2 + 0.245f * num2 * num2 * num2);
		float num4 = current - target;
		float num5 = target;
		float num6 = maxSpeed * smoothTime;
		num4 = glm::clamp(num4, -num6, num6);
		target = current - num4;
		float num7 = (velocity + num * num4) * deltaTime;
		float num8 = target + (num4 + num7) * num3;
		if (num5 - current > 0.0f == num8 > num5)
		{
			num8 = num5;
			velocity = (num8 - num5) / deltaTime;
		}
		return num8;
	}

	glm::vec3 Math::SmoothDamp(const glm::vec3& current, const glm::vec3& target,
		glm::vec3& velocity, float smoothTime,
		const glm::vec3& maxSpeed = { FLT_MAX,FLT_MAX,FLT_MAX }, float deltaTime = Time::deltaTime())
	{
		return { SmoothDamp(current.x, target.x, velocity.x, smoothTime, maxSpeed.x, deltaTime),
			SmoothDamp(current.y, target.y, velocity.y, smoothTime, maxSpeed.y, deltaTime),
		SmoothDamp(current.z, target.z, velocity.z, smoothTime, maxSpeed.z, deltaTime) };
	}

}