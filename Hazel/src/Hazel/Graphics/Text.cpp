#include "hzpch.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Text.h"

#include <glad/glad.h>
#include "Hazel/Debug/Instrumentor.h"

namespace hazel
{

	//////////////////////////////////
	/// Font
	//////////////////////////////////

	Font::Font(const std::string& fontFile)
	{
		InitFont(fontFile);
	}

	void Font::InitFont(std::string fontFile)
	{
		FT_Library ft;
		if (FT_Init_FreeType(&ft))
			Log::ErrorCore("ERROR::FREETYPE: Could not init FreeType Library");

		FT_Face face;
		if (FT_New_Face(ft, fontFile.c_str(), 0, &face))
			Log::ErrorCore("ERROR::FREETYPE: Failed to load font");

		FT_Set_Pixel_Sizes(face, 0, 48);

		if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
			Log::ErrorCore("ERROR::FREETYTPE: Failed to load Glyph");

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		for (unsigned char ch = 0; ch < 128; ch++)
		{
			if (FT_Load_Char(face, ch, FT_LOAD_RENDER))
			{
				Log::ErrorCore("ERROR::FREETYTPE: Failed to load Glyph, char: {0}", ch);
				continue;
			}
			//Log::InfoCore("char: {0}, w:{1}, h:{2}, bx:{3}, by:{4}", (char)ch,
			//	face->glyph->bitmap.width,
			//	face->glyph->bitmap.rows,
			//	face->glyph->bitmap_left,
			//	face->glyph->bitmap_top
			//);
			Ref<Texture2D>tex(Texture2D::Create());
			tex->LoadFromMemory(face->glyph->bitmap.width, face->glyph->bitmap.rows,
				1, face->glyph->bitmap.buffer);

			Character newChar = {
				tex,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				(unsigned int)face->glyph->advance.x
			};

			m_Characters.insert(std::pair<unsigned char, Character>(ch, newChar));
		}
		FT_Done_Face(face);
		FT_Done_FreeType(ft);
	}

	//////////////////////////////////
	/// Text
	//////////////////////////////////

	Text::Text(const Font& font, const std::string& content)
		:m_Font(font), m_Content(content), m_Color({ 0.0f,0.0f,0.0f,1.0f })
	{
		InitMesh();
	}

	void Text::InitMesh()
	{
		HZ_PROFILE_FUNCTION();

		BufferLayout layout = {
			{ShaderDataType::Float3,"aPos"},
			{ShaderDataType::Float2,"aTexCoord"},
		};

		m_VBO.reset(VertexBuffer::Create(sizeof(float) * 6 * 5));
		m_VBO->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VBO);

		m_EBO.reset(IndexBuffer::Create(6));
		m_VertexArray->SetIndexBuffer(m_EBO);
	}



}