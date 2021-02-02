#pragma once

#include "Hazel/Core/Core.h"

#include<vector>
#include<functional>

using std::vector;
using std::function;

namespace hazel
{
	class Image
	{
	public:

		Image()
			:width(0), height(0), channel(0),
			loadMode(LoadMode::NONE)
		{}

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
		void LoadFromMemory(const int& w, const int& h, const int& ch, const vector<unsigned char>& data);

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
		/// Bind current data to Texture Image Cache, 
		/// and generate a 2D mipmap
		/// </summary>
		void Use()const;

		/// <summary>
		/// Deal image data with imageDealCallBack
		/// </summary>
		/// <param name="imageDealCallBack">The dealing method defined by user</param>
		void DealImage(function<void(int, int, int, vector<unsigned char>&)>&& imageDealCallBack)
		{
			imageDealCallBack(width, height, channel, imageData);
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

		int width, height, channel;

		vector<unsigned char> imageData;

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

		LoadMode loadMode;
	};
}
