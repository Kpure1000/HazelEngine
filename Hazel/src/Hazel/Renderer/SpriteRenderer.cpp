#include "hzpch.h"
#include "SpriteRenderer.h"

#include "Hazel/Debug/Instrumentor.h"

namespace hazel
{
	SceneData* SpriteRenderer::m_SceneData = new SceneData;

	SpriteRenderer::SpriteRendererData SpriteRenderer::m_RenderData = SpriteRenderer::SpriteRendererData();

	void SpriteRenderer::Init()
	{
		HZ_PROFILE_FUNCTION();
		RenderCommand::Init();

		m_RenderData.VAO.reset(VertexArray::Create());

		//  Dynamic VBO
		m_RenderData.VBO.reset(VertexBuffer::Create(sizeof(SpriteVertex) * m_RenderData.MaxVertices));
		m_RenderData.VBO->SetLayout({
			{ShaderDataType::Float3,"aPos"},
			{ShaderDataType::Float4,"aColor"},
			{ShaderDataType::Float2,"aTexCoord"},
			{ShaderDataType::Float,"aTexIndex"},
			});
		m_RenderData.VAO->AddVertexBuffer(m_RenderData.VBO);

		m_RenderData.VBBase = new SpriteVertex[m_RenderData.MaxVertices];
		m_RenderData.VBPtr = m_RenderData.VBBase;

		//  Generate indexBuffer
		auto spritesIndices = new unsigned int[m_RenderData.MaxIndices];
		unsigned int offset = 0;
		for (unsigned int i = 0; i < m_RenderData.MaxIndices; i += 6)
		{
			spritesIndices[i + 0] = offset + 0;
			spritesIndices[i + 1] = offset + 1;
			spritesIndices[i + 2] = offset + 2;

			spritesIndices[i + 3] = offset + 2;
			spritesIndices[i + 4] = offset + 3;
			spritesIndices[i + 5] = offset + 0;

			offset += 4;
		}
		Ref<IndexBuffer> quadIB(IndexBuffer::Create(spritesIndices, m_RenderData.MaxIndices));
		m_RenderData.VAO->SetIndexBuffer(quadIB);
		delete[] spritesIndices;

		//  White Texture
		m_RenderData.whiteTexture.reset(Texture2D::Create());
		unsigned char whiteData[4] = { 0xff,0xff ,0xff ,0xff };
		m_RenderData.whiteTexture->LoadFromMemory(1, 1, 4, whiteData);

		//  Texture slots
		int texSamplers[m_RenderData.MaxTextureSlots];
		for (int i = 0; i < m_RenderData.MaxTextureSlots; i++)
			texSamplers[i] = i;
		m_RenderData.textureSlots.at(0) = m_RenderData.whiteTexture;

		//  Texture shader
		m_RenderData.textureShader.reset(Shader::Create("../data/shader/Default/sprite_ulit.glsl"));
		m_RenderData.textureShader->Use();
		m_RenderData.textureShader->SetIntArray("_textures", m_RenderData.MaxTextureSlots, texSamplers);

		//  Set initial position of each vertex
		m_RenderData.spriteVertexPosition[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		m_RenderData.spriteVertexPosition[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		m_RenderData.spriteVertexPosition[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
		m_RenderData.spriteVertexPosition[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
	}

	void SpriteRenderer::Shutdown()
	{
		delete[] m_RenderData.VBBase;
	}

	void SpriteRenderer::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->ProjectMat = camera.GetProjectMat();
		m_SceneData->ViewProjectMat = camera.GetViewProjectMat();

		m_RenderData.textureShader->SetMatrix4("_view_prj", m_SceneData->ViewProjectMat);
	}

	void SpriteRenderer::EndScene()
	{
	}

	void SpriteRenderer::Submit(const Sprite& sprite, Transform& trans, const Shader& shader)
	{
		shader.Use();
		shader.SetMatrix4("_model", trans.GetTransMat());
		shader.SetMatrix4("_view_prj", m_SceneData->ViewProjectMat);

		sprite.GetVertexArray()->Bind();
		RenderCommand::DrawIndexed(sprite.GetVertexArray());
	}

	void SpriteRenderer::Submit(Transform& trans, const glm::vec4 color, const Ref<Texture2D> texture)
	{
		constexpr size_t quadVertexCount = 4;
		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

		if (m_RenderData.indexCount >= SpriteRendererData::MaxIndices)
			NextBatch();

		float textureIndex = 0.0f;
		for (int i = 1; i < m_RenderData.textureSlotIndex; i++)
		{
			if (*m_RenderData.textureSlots[i] == *texture)
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			if (m_RenderData.textureSlotIndex >= SpriteRendererData::MaxTextureSlots)
				NextBatch();

			textureIndex = (float)m_RenderData.textureSlotIndex;
			m_RenderData.textureSlots[m_RenderData.textureSlotIndex] = texture;
			m_RenderData.textureSlotIndex++;
		}

		for (size_t i = 0; i < quadVertexCount; i++)
		{
			m_RenderData.VBPtr->position = trans.GetTransMat() * m_RenderData.spriteVertexPosition[i];
			m_RenderData.VBPtr->color = color;
			m_RenderData.VBPtr->texCoods = textureCoords[i];
			m_RenderData.VBPtr->texIndex = textureIndex;
			//m_RenderData.VBPtr->TilingFactor = tilingFactor;
			m_RenderData.VBPtr++;
		}

		//  add 6 vertex indices
		m_RenderData.indexCount += 6;

		m_RenderData.stats.QuadCount++;
	}

	void SpriteRenderer::Submit(const Text& text, Transform& trans, const Shader& shader)
	{
		shader.Use();
		shader.SetMatrix4("_projection", m_SceneData->ProjectMat);
		shader.SetVector4("_textColor", text.GetColor());

		auto& content = text.GetText();
		auto characters = text.GetCharacters();
		auto scale = trans.GetScale();

		int textNumbers = 0;
		auto pos = trans.GetPosition();
		for (auto chStr : content)
		{
			Character ch = characters[chStr];

			if (chStr == '\n')
			{
				pos.y -= (ch.size.y << 1) * scale.y;
				pos.x = trans.GetPosition().x;
				continue;
			}

			float xpos = pos.x + ch.bearing.x * scale.x;
			float ypos = pos.y - (ch.size.y - ch.bearing.y) * scale.y;

			float w = ch.size.x * scale.x;
			float h = ch.size.y * scale.y;

			float vert[18] = {
				xpos,     ypos + h, pos.z,
				xpos,     ypos,     pos.z,
				xpos + w, ypos,     pos.z,

				xpos,     ypos + h, pos.z,
				xpos + w, ypos,     pos.z,
				xpos + w, ypos + h, pos.z
			};
			float texC[12] = {
				0.0, 0.0,
				0.0, 1.0,
				1.0, 1.0,

				0.0, 0.0,
				1.0, 1.0,
				1.0, 0.0
			};

			//  bind texture
			ch.texture->Bind(textNumbers);
			shader.SetSampler2D("_textTexture", textNumbers);
			//textNumbers++;

			text.GetVertexArray()->Bind();

			//  draw sub vertex buffer
			text.GetVertexBuffer_Vertex()->SetData(vert, sizeof(float) * 18);

			text.GetVertexBuffer_TexCoord()->SetData(texC, sizeof(float) * 12);

			RenderCommand::DrawBuffered(text.GetVertexArray());

			//  or draw sub index buffer
			/*unsigned int indi[6] = {
				0,1,2,
				5,4,3
			};*/
			//text->GetIndexBuffer()->SetData(indi, 6);
			//RenderCommand::DrawIndexed(text->GetVertexArray());

			//  offset 2^6 
			pos.x += (ch.advance >> 6) * scale.x;
		}
	}

	void SpriteRenderer::Flush()
	{
		if (m_RenderData.indexCount == 0)
			return; // Nothing to draw

		size_t dataSize = (size_t)((uint8_t*)m_RenderData.VBPtr - (uint8_t*)m_RenderData.VBBase);
		m_RenderData.VBO->SetData(m_RenderData.VBBase, dataSize);

		// Bind textures
		for (int i = 0; i < m_RenderData.textureSlotIndex; i++)
			m_RenderData.textureSlots[i]->Bind(i);

		RenderCommand::DrawIndexed(m_RenderData.VAO, m_RenderData.indexCount);
		m_RenderData.stats.DrawCalls++;
	}

	void SpriteRenderer::StartBatch()
	{
		m_RenderData.indexCount = 0;
		m_RenderData.VBPtr = m_RenderData.VBBase;
		m_RenderData.textureSlotIndex = 1;
	}

	void SpriteRenderer::NextBatch()
	{
		Flush();
		StartBatch();
	}
}