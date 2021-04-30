#pragma once

#include "ISdfBase.h"

namespace krt {

	class KRT_API SdfSphere : public ISdfBase {
	public:
		virtual bool Hit(const Transform& m_Trans, const Ray& r, const float& tMin, const float& tMax, HitRecord& result, SdfRecordType& sdfRec) const override;

		virtual bool Sdf(const glm::vec3& p, float& sdfResult) const override;

	private:
		static glm::vec2 GetSphereUV(const glm::vec3& normal);

	};

}