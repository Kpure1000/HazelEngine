#pragma once

#include "../Core/Ray.h"

namespace krt {

	class KRT_API Material {
	public:
		virtual bool Scatter()const = 0;
	};

	class KRT_API DiffuseMaterial : public Material {
	public:
		virtual bool Scatter() const override {
			return true;
		}

	};

}