#include "hzpch.h"

#include "OpenGLShader.h"

#include <fstream>
#include <regex>


#include <glad/glad.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Hazel/Log.h"

namespace hazel
{
	OpenGLShader::OpenGLShader(const std::string& filePath)
	{
#pragma region load shader code from file

		std::ifstream shaderIn;
		std::string shaderStr;
		shaderIn.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			shaderIn.open(filePath.c_str());
			std::stringstream vstream, fstream;
			vstream << shaderIn.rdbuf();
			shaderIn.close();
			shaderStr = vstream.str();
		}
		catch (std::ifstream::failure e)
		{
			Log::ErrorCore("Ifstram failed, exception:\n{0}", e.what());
		}

#pragma endregion

#pragma region preprocess
		std::string vert_str;
		std::string frag_str;
		std::regex regex_vertex("(#shader [\\s]*vertex)");		//  '#shader vertex'
		std::regex regex_fragment("(#shader [\\s]*fragment)");	//  '#shader fragment'
		std::string pre_proc_str;

		//  split by '#shader vertex'
		auto sp_first = std::vector<std::string>(
			std::sregex_token_iterator(shaderStr.begin(), shaderStr.end(), regex_vertex, -1),
			std::sregex_token_iterator());
		std::vector<std::string> sp_second;
		if (sp_first.size() > 0) //  found '#shader vertex'
		{
			pre_proc_str = (*(sp_first.end() - 1)); //  get the latter
			//  split by '#shader fragment'
			sp_second = std::vector<std::string>(
				std::sregex_token_iterator(pre_proc_str.begin(), pre_proc_str.end(), regex_fragment, -1),
				std::sregex_token_iterator());
			if (sp_second.size() > 1) //  vertex code is the former
			{
				vert_str = sp_second[0];
				frag_str = sp_second[1];
			}
			else
			{
				//  split by '#shader fragment'
				sp_first = std::vector<std::string>(
					std::sregex_token_iterator(shaderStr.begin(), shaderStr.end(), regex_fragment, -1),
					std::sregex_token_iterator());
				if (sp_first.size() > 0)
				{
					pre_proc_str = (*(sp_first.end() - 1)); //  get the latter
					//  split by '#shader vertex'
					sp_second = std::vector<std::string>(
						std::sregex_token_iterator(pre_proc_str.begin(), pre_proc_str.end(), regex_vertex, -1),
						std::sregex_token_iterator());
					if (sp_second.size() > 1) //  fragment code is the former
					{
						frag_str = sp_second[0];
						vert_str = sp_second[1];
					}
				}
			}
		}

#pragma endregion

#pragma region vertex shader
		
		auto pos_first = shaderStr.find_first_of("#shader");

		int isCompileSuccessed;

		//  cerate vertex shader
		unsigned int vShader;
		vShader = glCreateShader(GL_VERTEX_SHADER);
		//  load shader code
		const char* vShaderCode = vert_str.c_str();
		glShaderSource(vShader, 1, &vShaderCode, NULL);
		//  compile code
		glCompileShader(vShader);
		char infoLog[512];
		glGetShaderiv(vShader, GL_COMPILE_STATUS, &isCompileSuccessed);
		if (!isCompileSuccessed)
		{
			glGetShaderInfoLog(vShader, 512, NULL, infoLog);
			Log::ErrorCore("Vertex shader compilation failed, in file:\'{0}\'. Details:\n{1}",
				filePath, infoLog);
		}

#pragma endregion

#pragma region fragment shader

		//  cerate fragment shader
		unsigned int fShader;
		fShader = glCreateShader(GL_FRAGMENT_SHADER);
		//  load shader code
		const char* fShaderCode = frag_str.c_str();
		glShaderSource(fShader, 1, &fShaderCode, NULL);
		//  compile 
		glCompileShader(fShader);
		char finfoLog[512];
		glGetShaderiv(fShader, GL_COMPILE_STATUS, &isCompileSuccessed);
		if (!isCompileSuccessed)
		{
			glGetShaderInfoLog(fShader, 512, NULL, finfoLog);
			Log::ErrorCore("Fragment shader compilation failed, in file:\'{0}\'. Details:\n{1}",
				filePath, finfoLog);
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

#pragma region get shader name from path

		std::regex regex_div_slash("\\\\|\\/");
		std::vector<std::string> split_div_slash(
			std::sregex_token_iterator(filePath.begin(), filePath.end(), regex_div_slash, -1),
			std::sregex_token_iterator()
		);
		std::regex regex_dot("\\.");
		if (split_div_slash.size() > 0) {
			auto& slashed = split_div_slash[split_div_slash.size() - 1];
			std::vector<std::string> split_dot(
				std::sregex_token_iterator(slashed.begin(), slashed.end(), regex_dot, -1),
				std::sregex_token_iterator()
			);
			if (split_dot.size() > 0) {
				m_Name = split_dot[0];
			}
		}
		else {
			m_Name = "";
		}

#pragma endregion

	}
	
	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_ID);
	}

	void OpenGLShader::Use()const
	{
		glUseProgram(m_ID);
	}

	void OpenGLShader::UnUse()const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetBool(const std::string& name,
		const bool& value) const
	{
		SetInt(name, value);
	}

	void OpenGLShader::SetInt(const std::string& name,
		const int& value) const
	{
		glUniform1i(GetPropertyID(name), value);
	}

	void OpenGLShader::SetFloat(const std::string& name,
		const float& value) const
	{
		glUniform1f(GetPropertyID(name), value);
	}

	void OpenGLShader::SetVector2(const std::string& name,
		const glm::vec2& value) const
	{
		glUniform2f(GetPropertyID(name), value.x, value.y);
	}

	void OpenGLShader::SetVector3(const std::string& name,
		const glm::vec3& value) const
	{
		glUniform3f(GetPropertyID(name), value.x, value.y, value.z);
	}

	void OpenGLShader::SetVector4(const std::string& name,
		const glm::vec4& value)const
	{
		glUniform4f(GetPropertyID(name), value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::SetRGBA(const std::string& name, const glm::vec4& color) const
	{
		SetVector4(name, color);
	}

	void OpenGLShader::SetRGB(const std::string& name, const glm::vec4& color) const
	{
		SetVector3(name, std::move(glm::vec3(color[0], color[1], color[2])));

	}
	void OpenGLShader::SetMatrix4(const std::string& name, const glm::mat4 mat) const
	{
		glUniformMatrix4fv(GetPropertyID(name), 1, GL_FALSE, glm::value_ptr(mat));
	}

	void OpenGLShader::SetSampler2D(const std::string& name, const int& index) const
	{
		glUniform1i(GetPropertyID(name), index);
	}

	void OpenGLShader::SetArray(const std::string& name, const int& size, const float* data)const
	{
		glUniform1fv(GetPropertyID(name), size, data);
	}

	int OpenGLShader::GetPropertyID(const std::string& name) const
	{
		return glGetUniformLocation(m_ID, (name).c_str());
	}

}