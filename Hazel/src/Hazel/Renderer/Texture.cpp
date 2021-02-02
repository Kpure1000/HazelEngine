#include "hzpch.h"

#include <glad/glad.h>

#include "Texture.h"

namespace hazel
{
	const int Texture::MaxTextureIndices = GL_TEXTURE30 - GL_TEXTURE0;


	Texture::Texture() :m_ID(-1)
	{
	}

	Texture::~Texture()
	{
		//  TODO: need to release bind?
	}

	void Texture::LoadFromFile(const std::string& path)
	{
		Init();
		image.LoadFromFile(path.c_str());
	}

	void Texture::LoadFromMemory(int w, int h, int ch, unsigned char* data)
	{
		Init();
		image.LoadFromMemory(w, h, ch, data);
	}

	void Texture::LoadFromImage(const Image& image)
	{
		Init();
		this->image = image;
	}

	void Texture::Bind(const int& index)const
	{
		if (index < MaxTextureIndices)
		{
			glActiveTexture(GL_TEXTURE0 + index);
			glBindTexture(GL_TEXTURE_2D, m_ID);
			image.Use();
		}
	}

	void Texture::ReBind(const int& index) const
	{
		if (index < MaxTextureIndices)
		{
			glActiveTexture(GL_TEXTURE0 + index);
			glBindTexture(GL_TEXTURE_2D, m_ID);
		}
	}

	unsigned int Texture::GetID()const
	{
		return m_ID;
	}

	void Texture::Init()
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