#include "krtpch.h"

#include "../../include/Core/Scene.h"

namespace krt {

	Scene::Scene(const std::string& name, glm::ivec2 size,
		Ref<Camera> camera, Ref<IAccelBase>accel)
		: m_Name(name), m_Size(size), m_Camera(camera),
		m_Skybox(std::make_shared<Skybox>()), m_Accel(accel){
	}

}