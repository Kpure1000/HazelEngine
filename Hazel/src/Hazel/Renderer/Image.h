#pragma once

#include "Hazel/Core/Core.h"

#include<vector>
#include<functional>

#include<glm/glm.hpp>

namespace hazel
{
	class Image
	{
	public:

		Image()
			:m_Width(0), m_Height(0), m_Channel(0),
			m_LoadMode(LoadMode::NONE)
		{}

		inline size_t GetBufferSize()const { return m_Data.size(); }

		inline int GetWidth()const { return m_Width; }
		inline int GetHeight()const { return m_Height; }

		inline unsigned int GetChannelCount()const { return m_Channel; }

		const unsigned char* GetData()const { return m_Data.data(); }

	public:
		/// <summary>
		/// Load image from memory
		/// </summary>
		/// <param name="w">Width</param>
		/// <param name="h">Heigt</param>
		/// <param name="ch">Channel</param>
		/// <param name="data">Image data</param>
		void LoadFromMemory(const int& w, const int& h, const int& ch, unsigned char* data);

		/// <summary>
		/// Load image from a vector
		/// </summary>
		/// <param name="w">Width</param>
		/// <param name="h">Heigt</param>
		/// <param name="ch">Channel</param>
		/// <param name="data">Image data(in vector)</param>
		void LoadFromMemory(const int& w, const int& h, const int& ch, const std::vector<unsigned char>& data);

		/// <summary>
		/// Load image from file and set weather flip y-axis or not
		/// </summary>
		/// <param name="path"></param>
		/// <param name="isFlip"></param>
		void LoadFromFile(const std::string& path, bool isFlip);

		/// <summary>
		/// Load image from file
		/// </summary>
		/// <param name="path"></param>
		void LoadFromFile(const std::string& path)
		{
			LoadFromFile(path, true);
		}

		/// <summary>
		/// Deal image data with imageDealCallBack
		/// </summary>
		/// <param name="imageDealCallBack">The dealing method defined by user</param>
		void DealImage(std::function<void(int, int, int, std::vector<unsigned char>&)>&& imageDealCallBack)
		{
			imageDealCallBack(m_Width, m_Height, m_Channel, m_Data);
		}

		/// <summary>
		/// Save current data to PNG
		/// </summary>
		/// <param name="path">File path</param>
		void SaveData(const std::string& path);

	private:

		/// <summary>
		/// Check weather image data with data size
		/// </summary>
		/// <param name="size">Size of data vector</param>
		/// <returns>Size is not zero</returns>
		bool CheckBuffer(size_t size)const;

		int m_Width, m_Height, m_Channel;

		std::vector<unsigned char> m_Data;

		/// <summary>
		/// Load from where
		/// </summary>
		enum class LoadMode
		{
			NONE,
			LOAD_MEMORY,
			LOAD_FILE,
			LOAD_IMAGE
		};

		LoadMode m_LoadMode;
	};
}
