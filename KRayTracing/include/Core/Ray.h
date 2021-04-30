#pragma once
#include "Core.h"
#include <glm/glm.hpp>

namespace krt {

	class KRT_API Ray {
	public:
		Ray(glm::vec3 origin = glm::vec3(0.0f), glm::vec3 direct = { 0.0f,0.0f,1.0f }, float time = 0.0f);

		inline glm::vec3 Origin() const { return m_Origin; }

		inline glm::vec3 Direct() const { return m_Direct; }

		inline glm::vec3 PointTo(float t) const { return m_Origin + t * m_Direct; }

		inline float Time() const { return m_Time; }

		friend Ray operator*(const glm::mat4& mat, const Ray& ray);

	private:
		glm::vec3 m_Origin;

		glm::vec3 m_Direct;

		float m_Time;
	};

}
