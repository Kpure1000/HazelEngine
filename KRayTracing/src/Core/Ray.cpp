#include "krtpch.h"

#include "../../include/Core/Ray.h"

namespace krt {

	Ray::Ray(glm::vec3 origin, glm::vec3 direct, float time)
		: m_Origin(origin), m_Direct(direct), m_Time(time)
	{}

	Ray operator*(const glm::mat4& mat, const Ray& ray)
	{
		return { mat * glm::vec4(ray.m_Origin, 1.0f), mat * glm::vec4(ray.m_Direct, 1.0f) };
	}

}
