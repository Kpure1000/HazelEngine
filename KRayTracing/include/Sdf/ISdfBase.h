#pragma once

#include "../Core/Ray.h"
#include "../Core/Transform.h"

namespace krt {

	struct HitRecord;

	enum class KRT_API SdfRecordType {
		_FLASE,
		_TRUE,
		_A,
		_B
	};

	class KRT_API ISdfBase {
	public:
		virtual bool Hit(const Transform& m_Trans, const Ray& r, const float& tMin, const float& tMax,
			HitRecord& result, SdfRecordType& sdfRec)const = 0;

		virtual bool Sdf(const glm::vec3& p, float& sdfResult)const = 0;

	};

}