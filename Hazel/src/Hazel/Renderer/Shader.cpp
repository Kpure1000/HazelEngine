#include "hzpch.h"

#include "Shader.h"

#include<fstream>
#include<sstream>
#include<iostream>

#include <glad/glad.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Hazel/Renderer/Renderer.h"

#include "Hazel/Log.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace hazel
{
	Shader* Shader::Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
	{
		switch (Renderer::GetAPI()) {
		case hazel::RendererAPI::API::None: {
			Log::AssertCore(false, "Create Shader: Renderer API: None is currently not supported.");
			return nullptr;
			break;
		}
		case hazel::RendererAPI::API::OpenGL: {
			return new OpenGLShader(vertexShaderPath, fragmentShaderPath);
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
}