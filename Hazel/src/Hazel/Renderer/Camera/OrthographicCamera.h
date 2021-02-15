#pragma once

#include "Hazel/Core/Core.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace hazel
{
	class HAZEL_API OrthographicCamera
	{
	public:
		OrthographicCamera(const glm::vec2& left_bottom,const glm::vec2& right_top);

		inline const glm::vec3& GetPosition()const { return m_Position; }
		inline float GetRotation()const { return m_Rotation; }

		void SetPosition(const glm::vec3& position) 
		{
			m_Position = position; 
			m_IsUpdated = true;
		}
		void SetRotation(const float& rotation) 
		{
			m_Rotation = rotation; 
			m_IsUpdated = true;
		}

		const glm::mat4& GetProjectMat()
		{
			if (m_IsUpdated)
			{
				RecalculateMatrix();
				m_IsUpdated = false;
			}
			return m_Projection;
		}

		const glm::mat4& GetViewMat() 
		{
			if (m_IsUpdated)
			{
				RecalculateMatrix();
				m_IsUpdated = false;
			}
			return m_View;
		}

		const glm::mat4& GetViewProjectMat() 
		{
			if (m_IsUpdated)
			{
				RecalculateMatrix();
				m_IsUpdated = false;
			}
			return m_ViewProjection;
		}

		void SetProjection(const glm::vec2& left_bottom, const glm::vec2& right_top)
		{
			m_Projection = {
				glm::ortho(left_bottom.x, right_top.x, left_bottom.y, right_top.y,
				-10.0f, 100.0f)
			};
			m_IsUpdated = true;
		}

	private:
		void RecalculateMatrix();

	private:
		glm::mat4 m_Projection;
		glm::mat4 m_View;
		glm::mat4 m_ViewProjection;

		glm::vec3 m_Position;
		float m_Rotation;

		bool m_IsUpdated;
	};

}
