#include "hzpch.h"

#include "Shader.h"

#include<fstream>
#include<sstream>
#include<iostream>

#include <glad/glad.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Hazel/Renderer/Renderer.h"

#include "Hazel/Core/Log.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include "Hazel/Debug/Instrumentor.h"

namespace hazel
{
	Shader* Shader::Create(const std::string& filePath)
	{
		HZ_PROFILE_FUNCTION();

		switch (Renderer::GetAPI()) {
		case hazel::RendererAPI::API::None: {
			Log::AssertCore(false, "Create Shader: Renderer API: None is currently not supported.");
			return nullptr;
			break;
		}
		case hazel::RendererAPI::API::OpenGL: {
			return new OpenGLShader(filePath);
			break;
		}
		case hazel::RendererAPI::API::Direct3D: {
			Log::AssertCore(false, "Create Shader: RendererAPI: Direct3D is coming soon.");
			return nullptr;
			break;
		}
		}
		Log::AssertCore(false, "Create Shader: Unkown Renderer API!");
		return nullptr;
	}

	/////////////////////////////////////////
	/// Shader Manager
	/////////////////////////////////////////

	const Ref<Shader> ShaderManager::Get(const std::string& name) const
	{
		if (IsExist(name))
		{
			return m_ShaderLib.at(name);
		}
		return nullptr;
	}

	const Ref<Shader> ShaderManager::Load(const std::string& filePath)
	{
		HZ_PROFILE_FUNCTION();

		Ref<Shader>shader;
		shader.reset((Shader::Create(filePath)));
		Add(shader);
		return shader;
	}

	const Ref<Shader> ShaderManager::Load(const std::string& filePath, const std::string& name)
	{
		HZ_PROFILE_FUNCTION();

		Ref<Shader>shader;
		shader.reset((Shader::Create(filePath)));
		Add(name, shader);
		return shader;
	}

	void ShaderManager::Add(const std::string& name, const Ref<Shader>& shader)
	{
		HZ_PROFILE_FUNCTION();

		if (IsExist(name)) 
		{
			Log::WarnCore("Shader '{0}' existed.", name);
			return;
		}
		shader->SetName(name);
		m_ShaderLib[name] = shader;
	}

	void ShaderManager::Add(const Ref<Shader>& shader)
	{
		HZ_PROFILE_FUNCTION();

		Add(shader->GetName(), shader);
	}

	bool ShaderManager::IsExist(const std::string& name) const
	{
		return m_ShaderLib.find(name) != m_ShaderLib.end();
	}
}