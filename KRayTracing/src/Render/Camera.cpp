#include "krtpch.h"

#include "../../include/Render/Camera.h"

#include "../../include/Utility/KRTMath.h"

namespace krt {

	//////////////////////////////////////////////////
	/// ProjectionCamera
	//////////////////////////////////////////////////

	ProjectionCamera::ProjectionCamera(const glm::vec3& lookFrom, const glm::vec3& lookAt,
		float foV, float aspect, float aperture, float focusDistance)
		:Camera(lookAt - lookFrom), m_LookFrom(lookFrom), m_LookAt(lookAt), m_FoV(foV), m_Aspect(aspect), m_Aperture(aperture)
	{
		auto init_up = glm::vec3(0.0f, 1.0f, 0.0f);
		float theta = m_FoV * glm::pi<float>() / 180.0f;
		float half_height = tan(theta * 0.5f);
		float half_width = m_Aspect * half_height;

		m_LensRadius = m_Aperture * 0.5f;
		right = glm::normalize(glm::cross(m_Direct, init_up));
		up = glm::cross(right, m_Direct);
		left_bottom = m_LookFrom + m_Direct * focusDistance - half_width * focusDistance * right
			- half_height * focusDistance * up;
		horizontal = 2 * half_width * right * focusDistance;
		vertical = 2 * half_height * up * focusDistance;
	}

	Ray ProjectionCamera::GetRay(float u, float v) {
		auto rd = m_LensRadius * KRTMath::RandomUnitDisk();
		auto offset = rd.x * right + rd.y * up;
		return Ray(m_LookFrom + offset, left_bottom
			+ u * horizontal + v * vertical - m_LookFrom - offset);
	}

	Ray ProjectionCamera::GetRay(const glm::vec2& uv) {
		return GetRay(uv.x, uv.y);
	}

	void ProjectionCamera::SetOrigin(const glm::vec3& origin)
	{
	}

	void ProjectionCamera::SetFollow(const glm::vec3& origin)
	{
	}

	void ProjectionCamera::SetFoV(float fov)
	{
	}

	void ProjectionCamera::SetAspect(float aspect)
	{
	}

	void ProjectionCamera::SetAperture(float aperture)
	{
	}

	void ProjectionCamera::SetDirect(const glm::vec3& direct)
	{
	}

	//////////////////////////////////////////////////
	/// OrthographicCamera
	//////////////////////////////////////////////////

	OrthographicCamera::OrthographicCamera(const glm::vec3& direct, float aspect, const glm::vec2& zoom)
		:Camera(direct), m_Aspect(aspect), m_Zoom(zoom)
	{}

	Ray OrthographicCamera::GetRay(float u, float v)
	{
		return Ray();
	}

	Ray OrthographicCamera::GetRay(const glm::vec2& uv)
	{
		return Ray();
	}

	void OrthographicCamera::SetAspect(float aspect)
	{
	}

	void OrthographicCamera::SetZoom(const glm::vec2& zoom)
	{
	}

}
