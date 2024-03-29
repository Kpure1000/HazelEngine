#pragma once

#include <string>
#include <glm/glm.hpp>

#include "Hazel/Core/Core.h"

namespace hazel
{
	class HAZEL_API Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Use()const = 0;

		virtual void UnUse()const = 0;

		virtual const std::string& GetName()const = 0;

		virtual const void SetName(const std::string& name) = 0;

	public:
		virtual void SetBool(const std::string& name, const bool& value)const = 0;

		virtual void SetInt(const std::string& name, const int& value)const = 0;

		virtual void SetFloat(const std::string& name, const float& value)const = 0;

		virtual void SetVector2(const std::string& name, const glm::vec2& value)const = 0;

		virtual void SetVector3(const std::string& name, const glm::vec3& value)const = 0;

		virtual void SetVector4(const std::string& name, const glm::vec4& value)const = 0;

		virtual void SetRGBA(const std::string& name, const glm::vec4& color)const = 0;

		virtual void SetRGB(const std::string& name, const glm::vec4& color)const = 0;

		virtual void SetMatrix4(const std::string& name, const glm::mat4 mat)const = 0;

		virtual void SetSampler2D(const std::string& name, const int& index)const = 0;

		virtual void SetFloatArray(const std::string& name, const int& size, const float* data)const = 0;

		virtual void SetIntArray(const std::string& name, const int& size, const int* data)const = 0;

	public:
		static Shader* Create(const std::string& filePath);

	};

	class HAZEL_API ShaderManager
	{
	public:
		const Ref<Shader> Get(const std::string& name)const;

		const Ref<Shader> Load(const std::string& filePath);

		const Ref<Shader> Load(const std::string& filePath, const std::string& name);

		void Add(const std::string& name, const Ref<Shader>& shader);

		void Add(const Ref<Shader>& shader);


	private:
		bool IsExist(const std::string& name)const;

		std::unordered_map<std::string, Ref<Shader>> m_ShaderLib;
	};

}

