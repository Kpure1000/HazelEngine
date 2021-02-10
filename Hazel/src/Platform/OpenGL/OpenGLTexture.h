#pragma once
#include "Hazel/Renderer/Texture.h"

namespace hazel
{
	class OpenGLTexture : public Texture
	{
	public:
		explicit OpenGLTexture() :m_ID(0) 
		{
			m_Image = std::make_shared<Image>();
		}

		~OpenGLTexture() {}

		virtual void Bind(const int& index) const override;
		
		virtual void UnBind(const int& index) const override;

		virtual unsigned int GetID() const override;

	public:
		virtual void LoadFromFile(const std::string& path) override;

		virtual void LoadFromMemory(int w, int h, int ch, unsigned char* data) override;

		virtual void LoadFromImage(Ref<Image>image) override;

	private:

		void Init();

		/// <summary>
		/// Texture id
		/// </summary>
		unsigned int m_ID;

		/// <summary>
		/// Max texture numbers in GL
		/// </summary>
		const static int MaxTextureIndices;

	};
}

