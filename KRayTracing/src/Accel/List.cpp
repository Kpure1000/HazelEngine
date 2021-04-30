#include "krtpch.h"

#include <memory>

#include "../../include/Accel/List.h"

namespace krt {
	bool List::Hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const {
		HitRecord recTmp;
		bool isHited = false;
		float closet_so_far = tMax;
		for (auto& hit : m_Data) {
			if (hit->Hit(r, tMin, closet_so_far, recTmp)) {
				isHited = true;
				rec = recTmp;
				closet_so_far = rec.t;
			}
		}
		return isHited;
	}
	bool List::AddHitable(Ref<Hitable> hitable) {
		m_Data.push_back(hitable);
		return true;
	}
}