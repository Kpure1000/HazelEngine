#pragma once

#include "../Core/Ray.h"

namespace krt {

	class KRT_API Camera {
	public:
		Camera(const glm::vec3& direct) :m_Direct(glm::normalize(direct)) {}

		virtual ~Camera() {}

		virtual Ray GetRay(float u, float v) = 0;

		virtual Ray GetRay(const glm::vec2& uv) = 0;

		glm::vec3 GetDirect() const { return m_Direct; }

	protected:
		glm::vec3 m_Direct;

	};

	class KRT_API ProjectionCamera : public Camera {
	public:
		ProjectionCamera(const glm::vec3& lookFrom, const glm::vec3& lookAt, float foV,
			float aspect, float aperture, float focusDistance);

		virtual ~ProjectionCamera() override {}

		virtual Ray GetRay(float u, float v) override;

		virtual Ray GetRay(const glm::vec2& uv) override;

	public:
		inline glm::vec3 GetOrigin() const { return m_LookFrom; }
		inline glm::vec3 GetFollow() const { return m_LookAt; }
		inline float GetFoV() const { return m_FoV; }
		inline float GetAspect() const { return m_Aspect; }
		inline float GetAperture() const { return m_Aperture; }

		void SetOrigin(const glm::vec3& origin);
		void SetFollow(const glm::vec3& origin);
		void SetFoV(float fov);
		void SetAspect(float aspect);
		void SetAperture(float aperture);

		[[maybe_unused]]
		void SetDirect(const glm::vec3& direct);

	private:
		glm::vec3 m_LookFrom;

		glm::vec3 m_LookAt;

		float m_FoV;

		float m_Aspect;

		float m_Aperture;

	private:
		// tmp
		float m_LensRadius;

		glm::vec3 right, up, left_bottom, horizontal, vertical;

	};

	class KRT_API OrthographicCamera : public Camera {
	public:
		OrthographicCamera(const glm::vec3& direct = { 0.0f,0.0f,1.0f },
			float aspect = 0.75f, const glm::vec2& zoom = { 1.0f,1.0f });

		virtual ~OrthographicCamera() override {}

		virtual Ray GetRay(float u, float v) override;

		virtual Ray GetRay(const glm::vec2& uv) override;

	public:
		inline float GetAspect() const { return m_Aspect; }
		inline glm::vec2 GetZoom() const { return m_Zoom; }

		void SetAspect(float aspect);
		void SetZoom(const glm::vec2& zoom);

	private:
		float m_Aspect;

		glm::vec2 m_Zoom;

	};

}