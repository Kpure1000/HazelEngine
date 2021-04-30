#pragma once
#include "../Render/Skybox.h"
#include "../Render/Camera.h"
#include "../Accel/IAccelBase.h"

namespace krt {

	class KRT_API Scene {
	public:
		Scene(const std::string& name, glm::ivec2 size,
			Ref<Camera> camera, Ref<IAccelBase>accel);

		inline std::string GetName() const { return m_Name; }

		inline glm::ivec2 GetSize() const { return m_Size; }

		inline const Ref<Camera> GetCamera() const { return m_Camera; }

		glm::vec3 GetSky(const glm::vec3& normal) const { return m_Skybox->GetSky(normal); }

	public:
		void PushObject(Ref<Hitable> object) { m_Accel->AddHitable(object); }

		const Ref<IAccelBase> GetObjects() const { return m_Accel; }

	private:
		std::string m_Name;

		glm::ivec2 m_Size;

		Ref<IAccelBase> m_Accel;

		Ref<Camera> m_Camera;

		Ref<Skybox> m_Skybox;

	};

}