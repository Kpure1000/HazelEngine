#include "krtpch.h"

#include "../../include/Core/Transform.h"

namespace krt {

	Transform::Transform()
		: m_Position(glm::vec3(0.0f)), m_Rotation({ 0.0f, 0.0f, 1.0f }), m_Scale(glm::vec3(1.0f)),
		m_Origin(glm::vec3(0.0f)), m_Angle(0.0f), m_TransMat(glm::mat4(1.0f))
	{
		CalculateMat();
	}

	void Transform::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		CalculateMat();
	}

	void Transform::SetOrigin(const glm::vec3& origin)
	{
		m_Origin = origin;
		CalculateMat();
	}

	void Transform::SetRotation(const glm::vec3& rotation)
	{
		m_Rotation = rotation;
		CalculateMat();
	}

	void Transform::SetScale(const glm::vec3& scale)
	{
		m_Scale = scale;
		CalculateMat();
	}

	void Transform::CalculateMat()
	{
		m_TransMat = glm::mat4(1.0);
		m_TransMat = glm::translate(m_TransMat, m_Position);
		m_TransMat = glm::rotate(m_TransMat, m_Angle, m_Rotation);
		m_TransMat = glm::scale(m_TransMat, m_Scale);
		m_TransMat = glm::translate(m_TransMat, m_Origin);

		m_TransMatIn = glm::inverse(m_TransMat);
	}

}
