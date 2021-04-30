#include "hzpch.h"

#include "Image.h"

#include <glad/glad.h>

#include <stb_image.h>
#include <stb_image_write.h>

#include "Hazel/Core/Log.h"
#include "Hazel/Debug/Instrumentor.h"

using std::vector;
using std::function;

namespace hazel
{
	
	void Image::LoadFromMemory(const int& w, const int& h, const int& ch, unsigned char* data)
	{
		HZ_PROFILE_FUNCTION();

		m_LoadMode = LoadMode::LOAD_MEMORY;
		this->m_Width = w;
		this->m_Height = h;
		this->m_Channel = ch;
		m_Size = 2 * h * ch;
		m_Data = data;
		CheckBuffer(m_Size);
	}

	void Image::LoadFromMemory(const int& w, const int& h, const int& ch, vector<unsigned char>& data)
	{
		HZ_PROFILE_FUNCTION();

		m_LoadMode = LoadMode::LOAD_MEMORY;
		this->m_Width = w;
		this->m_Height = h;
		this->m_Channel = ch;
		m_Size = data.size();

		m_Data = data.data();
		CheckBuffer(m_Size);
	}

	void Image::LoadFromFile(const std::string& path, bool isFlip)
	{
		m_LoadMode = LoadMode::LOAD_FILE;
		stbi_set_flip_vertically_on_load(isFlip);
		{
			HZ_PROFILE_SCOPE(__FUNCSIG__"->stbi_load_and_data_parse");

			auto data = stbi_load(path.c_str(), &m_Width, &m_Height, &m_Channel, 0);
			m_Size = m_Width * m_Height * m_Channel;
			m_Data = data;
			//stbi_image_free(data);
		}
		CheckBuffer(m_Size);
	}

	void Image::SaveData(const std::string& path)
	{
		HZ_PROFILE_FUNCTION();

		if (stbi_write_png(path.c_str(), m_Width, m_Height, m_Channel, m_Data, 0) == 0)
		{
			Log::ErrorCore("Save image data error, in path \'{0}\'", path);
		}

	}
	bool Image::CheckBuffer(size_t size) const
	{
#ifdef HZ_DEBUG
		if (size == 0)
		{
			if (m_LoadMode == LoadMode::LOAD_FILE)
			{
				Log::WarnCore("Load Image Warning: from file.");
			}
			else
			{
				Log::WarnCore("Load Image Warning: from other source.");
			}
			return false;
		}
#endif
		return true;
	}
}
