#include "hzpch.h"

#include "Image.h"

#include <glad/glad.h>

#include <stb_image.h>
#include <stb_image_write.h>

#include "Hazel/Log.h"

namespace hazel
{
	
	void Image::LoadFromMemory(const int& w, const int& h, const int& ch, unsigned char* data)
	{
		loadMode = LoadMode::LOAD_MEMORY;
		this->width = w;
		this->height = h;
		this->channel = ch;

		imageData.reserve((size_t)w * (size_t)h * (size_t)ch);
		imageData.assign(data, data + (size_t)w * (size_t)h * (size_t)ch);
		CheckBuffer(imageData.size());
	}
	void Image::LoadFromMemory(const int& w, const int& h, const int& ch, const vector<unsigned char>& data)
	{
		loadMode = LoadMode::LOAD_MEMORY;
		this->width = w;
		this->height = h;
		this->channel = ch;
		imageData = data;
		CheckBuffer(imageData.size());
	}
	void Image::LoadFromFile(const std::string& path, bool isFlip)
	{
		loadMode = LoadMode::LOAD_FILE;
		stbi_set_flip_vertically_on_load(isFlip);

		auto data = stbi_load(path.c_str(), &width, &height, &channel, 0);
		imageData.reserve((size_t)width * (size_t)height * (size_t)channel);
		imageData.assign(data, data + (size_t)width * (size_t)height * (size_t)channel);
		stbi_image_free(data);
		CheckBuffer(imageData.size());
	}
	void Image::Use() const
	{
		if (imageData.size() != 0 && loadMode != LoadMode::NONE)
		{
			if (channel == 1)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, imageData.data());
				glGenerateMipmap(GL_TEXTURE_2D);
			}
			if (channel == 3)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData.data());
				glGenerateMipmap(GL_TEXTURE_2D);
			}
			else if (channel == 4)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData.data());
				glGenerateMipmap(GL_TEXTURE_2D);
			}
			else
			{
				Log::ErrorCore("Texture image channel numbers error.");
			}
		}
		else
		{
			Log::ErrorCore("Image Buffer is Empty!");
		}

	}
	void Image::SaveData(const std::string& path)
	{
		if (stbi_write_png(path.c_str(), width, height, channel, imageData.data(), 0) == 0)
		{
			Log::ErrorCore("Save image data error, in path \'{0}\'", path);
		}

	}
	bool Image::CheckBuffer(size_t size) const
	{

		if (size == 0)
		{
			if (loadMode == LoadMode::LOAD_FILE)
			{
				Log::ErrorCore("Load Image Error: from file.");
			}
			else
			{
				Log::ErrorCore("Load Image Error: from other source.");
			}
			return false;
		}
		return true;
	}
}
