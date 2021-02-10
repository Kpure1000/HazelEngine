#include "hzpch.h"

#include "OrthographicCamera.h"

namespace hazel
{
	OrthographicCamera::OrthographicCamera(const glm::vec2& left_bottom, const glm::vec2& right_top)
		:m_Projection(glm::ortho(left_bottom.x, right_top.x, left_bottom.y, right_top.y, -10.0f, 100.0f)),
		m_View(1.0), m_ViewProjection(1.0),
		m_Position(0.0), m_Rotation(0.0f), m_IsUpdated(false)
	{
		RecalculateMatrix();
	}

	void OrthographicCamera::RecalculateMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f));

		m_View = glm::inverse(transform);
		m_ViewProjection = m_Projection * m_View;
	}
}
