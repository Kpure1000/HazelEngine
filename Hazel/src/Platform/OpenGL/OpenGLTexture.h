#pragma once
#include "Hazel/Renderer/Texture.h"

namespace hazel
{
	class OpenGLTexture : public Texture2D
	{
	public:
		explicit OpenGLTexture() :m_ID(0) 
		{
			m_Image = std::make_shared<Image>();
		}

		~OpenGLTexture() {}

		virtual void Bind(const int& index) const override;
		
		[[deprecated("Deleted method: GetID")]]
		inline virtual unsigned int GetID() const override { return m_ID; }

		inline virtual bool operator==(const Texture& other)const override
		{
			return m_ID == ((OpenGLTexture&)other).m_ID;
		}

	public:
		virtual void LoadFromFile(const std::string& path) override;

		virtual void LoadFromMemory(int w, int h, int ch, unsigned char* data) override;

		virtual void LoadFromImage(Ref<Image>image) override;

	private:

		void InitBeforeLoad();

		void BindAfterLoad();

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

