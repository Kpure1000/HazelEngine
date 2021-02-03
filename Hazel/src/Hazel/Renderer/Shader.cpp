#include "hzpch.h"

#include<fstream>
#include<sstream>
#include<iostream>

#include <glad/glad.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

#include "Hazel/Log.h"

namespace hazel
{
	Shader::Shader() :m_ID(-1)
	{
	}

	Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
	{
#pragma region load shader code from file

		char* vshaderCode;
		char* fshaderCode;
		std::ifstream vertIn;
		std::ifstream fragIn;
		std::string vstr, fstr;
		vertIn.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fragIn.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			vertIn.open(vertexShaderPath.c_str());
			fragIn.open(fragmentShaderPath.c_str());
			std::stringstream vstream, fstream;
			vstream << vertIn.rdbuf();
			fstream << fragIn.rdbuf();
			vertIn.close();
			fragIn.close();
			vstr = vstream.str();
			fstr = fstream.str();
		}
		catch (std::ifstream::failure e)
		{
			Log::ErrorCore("Ifstram failed, exception:\n{0}", e.what());
		}
		vshaderCode = (char*)vstr.c_str();
		fshaderCode = (char*)fstr.c_str();

#pragma endregion

#pragma region vertex shader
		int isCompileSuccessed;

		//  cerate vertex shader
		unsigned int vShader;
		vShader = glCreateShader(GL_VERTEX_SHADER);
		//  load shader code

		glShaderSource(vShader, 1, &vshaderCode, NULL);
		//  compile code
		glCompileShader(vShader);
		char infoLog[512];
		glGetShaderiv(vShader, GL_COMPILE_STATUS, &isCompileSuccessed);
		if (!isCompileSuccessed)
		{
			glGetShaderInfoLog(vShader, 512, NULL, infoLog);
			Log::ErrorCore("Vertex shader compilation failed, in file:\'{0}\'. Details:\n{1}",
				vertexShaderPath, infoLog);
		}

#pragma endregion

#pragma region fragment shader

		//  cerate fragment shader
		unsigned int fShader;
		fShader = glCreateShader(GL_FRAGMENT_SHADER);
		//  load shader code

		glShaderSource(fShader, 1, &fshaderCode, NULL);
		//  compile 
		glCompileShader(fShader);
		char finfoLog[512];
		glGetShaderiv(fShader, GL_COMPILE_STATUS, &isCompileSuccessed);
		if (!isCompileSuccessed)
		{
			glGetShaderInfoLog(fShader, 512, NULL, finfoLog);
			Log::ErrorCore("Fragment shader compilation failed, in file:\'{0}\'. Details:\n{1}",
				fragmentShaderPath, finfoLog);
		}

#pragma endregion

#pragma region shader program

		m_ID = glCreateProgram();
		//  add shader to program
		glAttachShader(m_ID, vShader);
		glAttachShader(m_ID, fShader);
		//  link shaders from program
		glLinkProgram(m_ID);

		char pinfoLog[512];
		glGetProgramiv(m_ID, GL_LINK_STATUS, &isCompileSuccessed);
		if (!isCompileSuccessed) {
			glGetProgramInfoLog(m_ID, 512, NULL, pinfoLog);
			Log::ErrorCore("Shader program link failed. Details:\n{0}", pinfoLog);
		}

		//  release shaders
		glDeleteShader(vShader);
		glDeleteShader(fShader);

#pragma endregion

	}

	Shader::~Shader()
	{
		glDeleteProgram(m_ID);
	}

	int Shader::GetID() const
	{
		return m_ID;
	}

	void Shader::Use()const
	{
		glUseProgram(m_ID);
	}

	void Shader::UnUse()const
	{
		glUseProgram(0);
	}

	void Shader::SetBool(const std::string& name,
		const bool& value) const
	{
		SetInt(name, value);
	}

	void Shader::SetInt(const std::string& name,
		const int& value) const
	{
		glUniform1i(GetPropertyID(name), value);
	}

	void Shader::SetFloat(const std::string& name,
		const float& value) const
	{
		glUniform1f(GetPropertyID(name), value);
	}

	void Shader::SetVector2(const std::string& name,
		const glm::vec2& value) const
	{
		glUniform2f(GetPropertyID(name), value.x, value.y);
	}

	void Shader::SetVector3(const std::string& name,
		const glm::vec3& value) const
	{
		glUniform3f(GetPropertyID(name), value.x, value.y, value.z);
	}

	void Shader::SetVector4(const std::string& name,
		const glm::vec4& value)const
	{
		glUniform4f(GetPropertyID(name), value.x, value.y, value.z, value.w);
	}

	void Shader::SetRGBA(const std::string& name, const glm::vec4& color) const
	{
		SetVector4(name, color);
	}

	void Shader::SetRGB(const std::string& name, const glm::vec4& color) const
	{
		SetVector3(name, std::move(glm::vec3(color[0], color[1], color[2])));

	}
	void Shader::SetMatrix4(const std::string& name, const glm::mat4 mat) const
	{
		glUniformMatrix4fv(GetPropertyID(name), 1, GL_FALSE, glm::value_ptr(mat));
	}

	void Shader::SetSampler2D(const std::string& name, const int& index) const
	{
		glUniform1i(GetPropertyID(name), index);
	}

	void Shader::SetArray(const std::string& name, const int& size, const float* data)const
	{
		glUniform1fv(GetPropertyID(name), size, data);
	}

	int Shader::GetPropertyID(const std::string& name) const
	{
		return glGetUniformLocation(m_ID, (name).c_str());
	}
}