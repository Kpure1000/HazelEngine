#include "krtpch.h"

#include "../../include/Sdf/SdfSphere.h"
#include "../../include/Hit/Hitable.h"

namespace krt {

	bool SdfSphere::Hit(const Transform& m_Trans, const Ray& r, const float& tMin, const float& tMax, HitRecord& result, SdfRecordType& sdfRec) const
	{
		auto center = m_Trans.GetPosition();
		float radius = (float)m_Trans.GetScale().x;
		auto o2c = r.Origin() - center;
		float a = glm::dot(r.Direct(), r.Direct());
		float b = 2.0f * glm::dot(o2c, r.Direct());
		float c = glm::dot(o2c, o2c) - radius * radius;
		float discriminant = b * b - 4.0f * a * c;
		if (discriminant > 0)
		{
			result.t = (-b - sqrtf(discriminant)) / (2.0f * a);
			if (result.t > tMin && result.t < tMax)
			{
				result.hitPoint = r.PointTo(result.t);
				result.normal = (result.hitPoint - center) / radius;
				result.uv = GetSphereUV(result.normal);
				return true;
			}
			result.t = (-b + sqrtf(discriminant)) / (2.0f * a);
			if (result.t > tMin && result.t < tMax)
			{
				result.hitPoint = r.PointTo(result.t);
				result.normal = (result.hitPoint - center) / radius;
				result.uv = GetSphereUV(result.normal);
				return true;
			}
		}
		return false;
	}

	bool SdfSphere::Sdf(const glm::vec3& p, float& sdfResult) const
	{
		return false;
	}

	glm::vec2 SdfSphere::GetSphereUV(const glm::vec3& normal)
	{
		float cosY = normal.y;
		float cosX = normal.x / sqrt(normal.x * normal.x + normal.z * normal.z);
		constexpr float pi_div = 1.0f / glm::pi<float>();
		return {
			(normal.z > 0.0f) ?
				(acos(cosX) * pi_div * 0.5f) :
				(1 - acos(cosX) * pi_div * 0.5f) ,
			acos(cosY) * pi_div
		};
	}

}