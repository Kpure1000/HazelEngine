#pragma once

#include "RenderCommand.h"
#include "RenderData.h"

#include "Hazel/Renderer/Shader.h"
#include "Hazel/Renderer/Camera/OrthographicCamera.h"

#include "Hazel/Graphics/Transform.h"
#include "Hazel/Graphics/Mesh/Sprite.h"
#include "Hazel/Graphics/Text.h"

namespace hazel
{
	class HAZEL_API SpriteRenderer
	{
		struct Statistics;

	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		[[deprecated("Old Submit Method: Sprite")]]
		static void Submit(const Sprite& sprite,
			Transform& trans, const Shader& shader);

		/// <summary>
		/// Submit a sprite
		/// </summary>
		/// <param name="sprite"></param>
		/// <param name="trans"></param>
		/// <param name="texture"></param>
		/// <param name="color"></param>
		static void Submit(const Sprite& sprite, Transform& trans, const Ref<Texture2D> texture, const glm::vec4 color = glm::vec4(1.0f));

		[[deprecated("Old Submit Method: Text")]]
		static void Submit(const Text& text, Transform& trans, const Shader& shader);
		
		/// <summary>
		/// Submit a text (shoud call NewBatch between sprite and text submiting)
		/// </summary>
		/// <param name="text"></param>
		/// <param name="trans"></param>
		static void Submit(const Text& text, Transform& trans);

		static void Flush();

		/// <summary>
		/// Start a new batch
		/// </summary>
		static void NewBatch();

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

		inline static void ResetState() { memset(&m_RenderData.stats, 0, sizeof(Statistics)); }

		inline static Statistics GetState() { return m_RenderData.stats; }

	private:
		static void StartBatch();

	private:
		struct SpriteVertex
		{
			glm::vec3 position;
			glm::vec4 color;
			glm::vec2 texCoods;
			float texIndex;
		};

		struct Statistics
		{
			size_t DrawCalls = 0;
			size_t QuadCount = 0;

			size_t GetTotalVertexCount() const { return QuadCount * 4; }
			size_t GetTotalIndexCount() const { return QuadCount * 6; }
		};

		struct SpriteRendererData
		{
			static const size_t MaxSprites = 3000;
			static const size_t MaxVertices = MaxSprites * 4;
			static const size_t MaxIndices = MaxSprites * 6;
			static const size_t MaxTextureSlots = 31; // TODO: RenderCaps

			size_t textureSlotIndex = 1; // 0 = white texture
			size_t indexCount = 0;

			glm::vec4 spriteVertexPosition[4];
			glm::vec2 textureCoords[4];

			SpriteRenderer::Statistics stats;

			std::array<Ref<Texture2D>, MaxTextureSlots> textureSlots;

			SpriteVertex* VBBase = nullptr;
			SpriteVertex* VBPtr = nullptr;

			Ref<VertexArray> VAO;
			Ref<VertexBuffer> VBO;
			Ref<Shader> textureShader;
			Ref<Shader> textShader;
			Ref<Texture2D> whiteTexture;

		};

		static SpriteRendererData m_RenderData;

		static SceneData* m_SceneData;

	};
}