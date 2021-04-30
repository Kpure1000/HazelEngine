#pragma once
#include "../Core/Core.h"

#include <functional>

#include <glm/glm.hpp>

namespace krt {

	class KRT_API Skybox {
	public:
		using SkyFunc = std::function<glm::vec3(const glm::vec3& normal)>;

	public:
		Skybox()
		{
			m_SkyFunc = [](const glm::vec3& normal)-> glm::vec3 {

				float t = 0.5f * (normal.y + 1.0f);
				return { (1.0f - t) * glm::vec3(1.0f) + t * glm::vec3(0.5f,0.7f,1.0f) };
				//return { normal.x,normal.y,0.2f };
			};
		}

		void SetKeyFunc(const SkyFunc& skyFunc) { m_SkyFunc = skyFunc; }

		glm::vec3 GetSky(const glm::vec3& normal) const { return m_SkyFunc(normal); }

	private:
		SkyFunc m_SkyFunc;

	};

}