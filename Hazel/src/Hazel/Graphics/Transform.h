#pragma once

#include "Hazel/Core/Core.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace hazel
{
	class HAZEL_API Transform
	{
	public:

		/// <summary>
		/// Trasform
		/// </summary>
		Transform()
			: m_position(glm::vec3(0.0f)),
			m_origin(glm::vec3(0.0f)),
			m_rotation(glm::vec3(0.0f, 0.0f, 1.0f)), m_angle(0.0f),
			m_scale(glm::vec3(1.0f)),
			m_trans(glm::mat4(1.0f)),
			isUpdated(false)
		{}

		inline glm::vec3 GetPosition()const
		{
			return m_position;
		}

		inline glm::vec3 GetOrigin()const
		{
			return m_origin;
		}

		inline glm::vec3 GetRotation()const
		{
			return m_rotation;
		}

		inline glm::vec3 GetScale()const
		{
			return m_scale;
		}

		glm::mat4 GetTransMat();

		/// <summary>
		/// Set position
		/// </summary>
		/// <param name="position"></param>
		inline void SetPosition(const glm::vec3& position)
		{
			isUpdated = true;
			m_position = position;
		}

		inline void SetPosition(glm::vec3&& position)
		{
			isUpdated = true;
			m_position = std::move(position);
		}

		/// <summary>
		/// Set the local opriginal position of transform
		/// </summary>
		/// <param name="origin"></param>
		inline void SetOrigin(const glm::vec3& origin)
		{
			isUpdated = true;
			m_origin = origin;
		}

		inline void SetOrigin(glm::vec3&& origin)
		{
			isUpdated = true;
			m_origin = std::move(origin);
		}

		/// <summary>
		/// Set rotation
		/// </summary>
		/// <param name="rotation"></param>
		inline void SetRotation(const glm::vec3& rotation, const float& angle)
		{
			isUpdated = true;
			m_rotation = rotation;
			m_angle = angle;
		}

		inline void SetRotation(glm::vec3&& rotation, const float& angle)
		{
			isUpdated = true;
			m_rotation = std::move(rotation);
			m_angle = angle;
		}

		/// <summary>
		/// Set scale
		/// </summary>
		/// <param name="scale"></param>
		inline void SetScale(const glm::vec3& scale)
		{
			isUpdated = true;
			m_scale = scale;
		}

		inline void SetScale(glm::vec3&& scale)
		{
			isUpdated = true;
			m_scale = std::move(scale);
		}

		/// <summary>
		/// Rotate
		/// </summary>
		/// <param name="rotation">Axis</param>
		/// <param name="angle">Angle</param>
		void Rotate(const glm::vec3& rotation, const float& angle);

		/// <summary>
		/// Rotate arround a target position
		/// </summary>
		/// <param name="target">Target position</param>
		/// <param name="up">Up axis of rotate</param>
		/// <param name="speed">Angle speed</param>
		void RotateArround(const glm::vec3& target,
			const glm::vec3& up, const float& speed);

	private:

		glm::vec3 m_position;

		glm::vec3 m_origin;

		//  TODO: Might replace by quaternion
		glm::vec3 m_rotation;
		float m_angle;

		glm::vec3 m_scale;

		glm::mat4 m_trans;

		bool isUpdated;

	};
}

