#pragma once

#include "Hazel/Core/Core.h"

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<map>

#include "Image.h"

namespace hazel
{
	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual void Bind(const int& index)const = 0;

		virtual unsigned int GetID()const = 0;

		virtual bool operator==(const Texture& other)const = 0;

	public:
		virtual void LoadFromFile(const std::string& path) = 0;

		/// <summary>
		/// Load Data From Memory
		/// </summary>
		/// <param name="w">Width</param>
		/// <param name="h">Height</param>
		/// <param name="ch">Channel counts</param>
		/// <param name="data">Data</param>
		virtual void LoadFromMemory(int w, int h, int ch, unsigned char* data) = 0;

		/// <summary>
		/// Load data from image
		/// </summary>
		/// <param name="image">Image</param>
		virtual void LoadFromImage(Ref<Image>image) = 0;

		/// <summary>
		/// Deal with image data using method defined in callback
		/// </summary>
		/// <param name="imageDealCallback">Method defined how to deal with image</param>
		void DealImage(std::function<void(int, int, int, std::vector<unsigned char>&)>&& imageDealCallback)
		{
			m_Image->DealImage(std::move(imageDealCallback));
		}

	protected:

		/// <summary>
		/// Data
		/// </summary>
		Ref<Image> m_Image;

	};

	class Texture2D : public Texture
	{
	public:
		static Texture2D* Create();
	};

}