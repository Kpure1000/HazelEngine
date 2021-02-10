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
			return;
		}
		Log::ErrorCore("Image Buffer is Empty!");
	}

	////////////////////////////////////////////
	/// Load Texture Data
	////////////////////////////////////////////

	void OpenGLTexture::LoadFromFile(const std::string& path)
	{
		InitBeforeLoad();
		m_Image->LoadFromFile(path.c_str());
		BindAfterLoad();
	}

	void OpenGLTexture::LoadFromMemory(int w, int h, int ch, unsigned char* data)
	{
		InitBeforeLoad();
		m_Image->LoadFromMemory(w, h, ch, data);
		BindAfterLoad();
	}

	void OpenGLTexture::LoadFromImage(Ref<Image>image)
	{
		InitBeforeLoad();
		this->m_Image = image;
		BindAfterLoad();
	}

	void OpenGLTexture::InitBeforeLoad()
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

	void OpenGLTexture::BindAfterLoad()
	{
		if (m_Image->GetBufferSize() != 0)
		{
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

}