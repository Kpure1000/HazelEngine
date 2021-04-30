#pragma once

#include "../Hit/Hitable.h"

namespace krt {

	class KRT_API IAccelBase {
	public:
		virtual bool Hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const = 0;

		virtual bool AddHitable(Ref<Hitable> hitable) = 0;
	};

}