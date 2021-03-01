#pragma once

#include "Hazel/Core/Core.h"

#include "Hazel/Renderer/Texture.h"
#include "Hazel/Graphics/Mesh/Mesh.h"

#include <string>
#include <map>

namespace hazel
{

	struct Character
	{
		Ref<Texture2D> texture;
		glm::ivec2 size;
		glm::ivec2 bearing;
		unsigned int advance;
	};

	class Text;

	class Font
	{
	public:
		Font(const std::string& fontFile);

	private:
		friend Text;

		void InitFont(std::string fontFile);

		std::map<unsigned char, Character> m_Characters;
	};

	class Text : public Mesh
	{
	public:
		Text(const Font& font, const std::string& content = "");

		inline const std::string& GetText()const { return m_Content; }
		inline const glm::vec4& GetColor()const { return m_Color; }

		inline void SetText(const std::string& text) { m_Content = text; }
		inline void SetColor(const glm::vec4& color) { m_Color = color; }

		inline void SetFont(const Font& font) { m_Font = font; }

		inline Ref<VertexBuffer> GetVertexBuffer_Vertex() { return m_VBO_VERT; }
		inline Ref<VertexBuffer> GetVertexBuffer_TexCoord() { return m_VBO_TEXC; }
		inline Ref<IndexBuffer> GetIndexBuffer() { return m_EBO; }

		inline const std::map<unsigned char, Character>& GetCharacters()const { return m_Font.m_Characters; }

		const Character& GetCharacter(unsigned char ch) { return m_Font.m_Characters[ch]; }

	private:
		void InitMesh();

		std::string m_Content;
		glm::vec4 m_Color;

		Font m_Font;

		Ref<VertexBuffer> m_VBO_VERT;
		Ref<VertexBuffer> m_VBO_TEXC;
		Ref<IndexBuffer> m_EBO;

	};
}
