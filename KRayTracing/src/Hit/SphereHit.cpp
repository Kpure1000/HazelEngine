#include "krtpch.h"

#include "../../include/Hit/SphereHit.h"
#include "../../include/Sdf/SdfSphere.h"

namespace krt {

	SphereHit::SphereHit() 
		:Hitable(std::make_shared<DiffuseMaterial>(), std::make_shared<SdfSphere>())
	{
	}

	bool SphereHit::Hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const
	{
		SdfRecordType sdfRec;
		auto isHit = m_Sdf->Hit(*m_Trans, r, tMin, tMax, rec, sdfRec);
		return isHit;
	}

}
