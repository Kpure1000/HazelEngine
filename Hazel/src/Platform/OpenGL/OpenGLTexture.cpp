#include "hzpch.h"

#include "OpenGLTexture.h"

#include <glad/glad.h>

#include "Hazel/Core/Log.h"
#include "Hazel/Debug/Instrumentor.h"

namespace hazel
{
	const int OpenGLTexture::MaxTextureIndices = GL_TEXTURE31 - GL_TEXTURE0;

	void OpenGLTexture::Bind(const int& index)const
	{
		if (index < MaxTextureIndices)
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
		Ref<Image> image = std::make_shared<Image>();
		image->LoadFromFile(path.c_str());
		BindAfterLoad(image);
	}

	void OpenGLTexture::LoadFromMemory(int w, int h, int ch, unsigned char* data)
	{
		InitBeforeLoad();
		Ref<Image> image = std::make_shared<Image>();
		image->LoadFromMemory(w, h, ch, data);
		BindAfterLoad(image);
	}

	void OpenGLTexture::LoadFromImage(Ref<Image>image)
	{
		InitBeforeLoad();
		BindAfterLoad(image);
	}

	void OpenGLTexture::UpdateFromMemory(int w, int h, int ch, unsigned char* data)
	{
		Ref<Image> image = std::make_shared<Image>();
		image->LoadFromMemory(w, h, ch, data);
		BindAfterLoad(image);
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

	void OpenGLTexture::BindAfterLoad(Ref<Image> image)
	{
		HZ_PROFILE_FUNCTION();

#ifdef HZ_DEBUG
		if (image->GetBufferSize() == 0)
		{
			Log::WarnCore("Texture Loading Warning: Image Buffer is Empty!");
		}
#endif
		switch (image->GetChannelCount())
		{
		case 1: {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, image->GetWidth(), image->GetHeight(), 0, GL_RED, GL_UNSIGNED_BYTE, image->GetData());
			break;
		}
		case 3: {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->GetWidth(), image->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image->GetData());
			break;
		}
		case 4: {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->GetWidth(), image->GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image->GetData());
			break;
		}
		default:
			Log::ErrorCore("Texture image channel numbers error.");
			return;
		}
		glGenerateMipmap(GL_TEXTURE_2D);

		m_Size = { image->GetWidth(),image->GetHeight() };

		return;
	}

}