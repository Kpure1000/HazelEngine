#pragma once

#include "../Core/Transform.h"
#include "../Core/Ray.h"
#include "../Render/Material.h"
#include "../Sdf/ISdfBase.h"

namespace krt {

	struct KRT_API HitRecord {
		float t = 0.0f;

		glm::vec3 hitPoint=glm::vec3(0.0f);

		glm::vec3 normal = glm::vec3(1.0f);

		//Material* mat = nullptr;

		glm::vec2 uv = glm::vec2(0.0f);

		bool isInRange = false;

	};

	class KRT_API Hitable {
	public:
		Hitable(Ref<Material> material, Ref<ISdfBase> sdf)
			: m_Material(material), m_Sdf(sdf), m_Trans(std::make_shared<Transform>())
		{}

		virtual ~Hitable() {}

		virtual bool Hit(const Ray& r, float tMin, float tMax, HitRecord& rec)const = 0;

		Transform GetTransform() const { return *m_Trans; }
		Transform& GetTransform() { return *m_Trans; }

	protected:
		Ref<Material> m_Material;
		
		Ref<ISdfBase> m_Sdf;

		Ref<Transform> m_Trans;
	};

}