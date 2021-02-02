#pragma once

#include <string>
#include <glm/glm.hpp>

#include "Hazel/Core/Core.h"

namespace hazel
{
	class HAZEL_API Shader
	{
	public:
		Shader();

		Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

		~Shader();

		int GetID()const;

		void Use()const;

	public: //  set value in shader

		void SetBool(const std::string& name, const bool& value)const;

		void SetInt(const std::string& name, const int& value)const;

		void SetFloat(const std::string& name, const float& value)const;

		void SetVector2(const std::string& name, const glm::vec2& value)const;

		void SetVector3(const std::string& name, const glm::vec3& value)const;

		void SetVector4(const std::string& name, const glm::vec4& value)const;

		void SetRGBA(const std::string& name, const glm::vec4& color)const;

		void SetRGB(const std::string& name, const glm::vec4& color)const;

		void SetMatrix4(const std::string& name, const glm::mat4 mat)const;

		void SetSampler2D(const std::string& name, const int& index)const;

		void SetArray(const std::string& name, const int& size, const float* data)const;

	private:

		/// <summary>
		/// Get property ID by shaderID and property name
		/// </summary>
		/// <param name="name"></param>
		/// <returns></returns>
		int GetPropertyID(const std::string& name)const;

		/// <summary>
		/// id of shader program
		/// </summary>
		unsigned int m_ID;

	};
}

