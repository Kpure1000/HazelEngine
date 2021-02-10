#include "hzpch.h"

#include "OpenGLTexture.h"

#include <glad/glad.h>

#include "Hazel/Log.h"

namespace hazel
{
	const int OpenGLTexture::MaxTextureIndices = GL_TEXTURE30 - GL_TEXTURE0;

	void OpenGLTexture::Bind(const int& index)const
	{
		if (index < MaxTextureIndices && m_Image->GetBufferSize() != 0)
		{
			glActiveTexture(GL_TEXTURE0 + index);
			glBindTexture(GL_TEXTURE_2D, m_ID);

			switch (m_Image->GetChannelCount())
			{
			case 1: {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_Image->GetWidth(), m_Image->GetHeight(), 0, GL_RED, GL_UNSIGNED_BYTE, m_Image->GetData());
				break;
			}
			case 3: {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Image->GetWidth(), m_Image->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, m_Image->GetData());
				break;
			}
			case 4: {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Image->GetWidth(), m_Image->GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Image->GetData());
				break;
			}
			default:
				Log::ErrorCore("Texture image channel numbers error.");
				return;
			}
			glGenerateMipmap(GL_TEXTURE_2D);
			return;
		}
		Log::ErrorCore("Image Buffer is Empty!");
	}

	void OpenGLTexture::UnBind(const int& index) const
	{
		glActiveTexture(GL_TEXTURE0 + index);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	unsigned int OpenGLTexture::GetID()const
	{
		return m_ID;
	}

	////////////////////////////////////////////
	/// Load Texture Data
	////////////////////////////////////////////

	void OpenGLTexture::LoadFromFile(const std::string& path)
	{
		Init();
		m_Image->LoadFromFile(path.c_str());
	}

	void OpenGLTexture::LoadFromMemory(int w, int h, int ch, unsigned char* data)
	{
		Init();
		m_Image->LoadFromMemory(w, h, ch, data);
	}

	void OpenGLTexture::LoadFromImage(Ref<Image>image)
	{
		Init();
		this->m_Image = image;
	}

	void OpenGLTexture::Init()
	{
		glGenTextures(1, &m_ID);
		glBindTexture(GL_TEXTURE_2D, m_ID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		//  Mag filter
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		//  Anisotropic Filtering
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, GL_LINEAR_MIPMAP_LINEAR);
	}
}