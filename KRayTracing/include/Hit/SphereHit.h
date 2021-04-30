#pragma once

#include "Hitable.h"

namespace krt {

	class KRT_API SphereHit : public Hitable {
	public:
		SphereHit();

		virtual bool Hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const override;
		
	private:

	};

}
