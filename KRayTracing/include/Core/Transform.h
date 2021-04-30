#pragma once

#include "../Utility/KRTMath.h"

namespace krt {

	class KRT_API Transform {
	public:
		Transform();

		glm::vec3 GetPosition() const { return m_Position; }
		glm::vec3 GetOrigin() const { return m_Origin; }
		glm::vec3 GetRotation() const { return m_Rotation; }
		glm::vec3 GetScale() const { return m_Scale; }

		glm::mat4 GetTransMat() const { return m_TransMat; }
		glm::mat4 GetInversedMat() const { return m_TransMat; }

		operator glm::mat4()const {
			return m_TransMat;
		}

		void SetPosition(const glm::vec3& position);
		void SetOrigin(const glm::vec3& origin);
		void SetRotation(const glm::vec3& rotation);
		void SetScale(const glm::vec3& scale);

	private:
		void CalculateMat();

		glm::vec3 m_Position;
		glm::vec3 m_Origin;

		glm::vec3 m_Rotation;
		float m_Angle;

		glm::vec3 m_Scale;

		// transform matrix
		mutable glm::mat4 m_TransMat;

		// inversed transform matrix
		mutable glm::mat4 m_TransMatIn;

	};

}