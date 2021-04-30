#pragma once

#include "IAccelBase.h"

#include <vector>

namespace krt {

	class KRT_API List : public IAccelBase {
	public:
		virtual bool Hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const override;

		virtual bool AddHitable(Ref<Hitable> hitable) override;

	private:
		std::vector<Ref<Hitable>> m_Data;


	};

}