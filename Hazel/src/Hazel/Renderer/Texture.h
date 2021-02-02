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

		Texture();

		~Texture();

		/// <summary>
		/// Load Data From File by stbi
		/// </summary>
		/// <param name="path"></param>
		void LoadFromFile(const std::string& path);

		/// <summary>
		/// Load Data From Memory
		/// </summary>
		/// <param name="w"></param>
		/// <param name="h"></param>
		/// <param name="ch"></param>
		/// <param name="data"></param>
		void LoadFromMemory(int w, int h, int ch, unsigned char* data);

		/// <summary>
		/// Load data from image
		/// </summary>
		/// <param name="image"></param>
		void LoadFromImage(const Image& image);

		/// <summary>
		/// Bind current texture
		/// </summary>
		void Bind(const int& index)const;

		void ReBind(const int& index)const;

		/// <summary>
		/// Get id of texture
		/// </summary>
		/// <returns></returns>
		unsigned int GetID()const;

		[[deprecated("This constructor will be deleted")]]
		void SetID(const unsigned int& id)
		{
			m_ID = id;
		}

		void DealImage(function<void(int, int, int, vector<unsigned char>&)>&& imageDealCallBack)
		{
			image.DealImage(std::move(imageDealCallBack));
		}

	private:

		void Init();

		/// <summary>
		/// Texture id
		/// </summary>
		unsigned int m_ID;

		/// <summary>
		/// Data
		/// </summary>
		Image image;

		/// <summary>
		/// Max texture numbers in GL
		/// </summary>
		const static int MaxTextureIndices;

	};

	/// <summary>
	/// Mesh Texture
	/// </summary>
	struct MeshTex
	{
		Texture texture;

		std::string type;
	};
}