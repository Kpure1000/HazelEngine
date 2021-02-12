#pragma once
#include "Hazel/Renderer/Shader.h"
namespace hazel
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filePath);

		~OpenGLShader();

		virtual void Use()const override;

		virtual void UnUse()const override;

		virtual const std::string& GetName()const override { return m_Name; }

		virtual const void SetName(const std::string& name) override { m_Name = name; }

	public:
		virtual void SetBool(const std::string& name, const bool& value)const override;

		virtual void SetInt(const std::string& name, const int& value)const override;

		virtual void SetFloat(const std::string& name, const float& value)const override;

		virtual void SetVector2(const std::string& name, const glm::vec2& value)const override;

		virtual void SetVector3(const std::string& name, const glm::vec3& value)const override;

		virtual void SetVector4(const std::string& name, const glm::vec4& value)const override;

		virtual void SetRGBA(const std::string& name, const glm::vec4& color)const override;

		virtual void SetRGB(const std::string& name, const glm::vec4& color)const override;

		virtual void SetMatrix4(const std::string& name, const glm::mat4 mat)const override;

		virtual void SetSampler2D(const std::string& name, const int& index)const override;

		virtual void SetArray(const std::string& name, const int& size, const float* data)const override;

	private:
		/// <summary>
		/// Get property ID by shaderID and property name
		/// </summary>
		/// <param name="name"></param>
		/// <returns></returns>
		int GetPropertyID(const std::string& name)const;

	private:
		/// <summary>
		/// id of shader program
		/// </summary>
		unsigned int m_ID;

		std::string m_Name;

	};

}

