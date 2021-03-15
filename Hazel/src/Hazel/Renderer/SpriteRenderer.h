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
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Sprite& sprite,
			Transform& trans, const Shader& shader);

		static void Submit(Transform& trans, const glm::vec4 color, const Ref<Texture2D> texture);

		static void Submit(const Text& text,
			Transform& trans, const Shader& shader);

		static void Flush();

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		static void StartBatch();

		static void NextBatch();

	private:
		struct SpriteVertex
		{
			glm::vec3 position;
			glm::vec3 color;
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
			static const size_t MaxSprites = 20000;
			static const size_t MaxVertices = MaxSprites * 4;
			static const size_t MaxIndices = MaxSprites * 6;
			static const size_t MaxTextureSlots = 32; // TODO: RenderCaps

			size_t textureSlotIndex = 1; // 0 = white texture
			size_t indexCount = 0;

			glm::vec4 spriteVertexPosition[4];

			SpriteRenderer::Statistics stats;

			std::array<Ref<Texture2D>, MaxTextureSlots> textureSlots;

			SpriteVertex* VBBase = nullptr;
			SpriteVertex* VBPtr = nullptr;

			Ref<VertexArray> VAO;
			Ref<VertexBuffer> VBO;
			Ref<Shader> textureShader;
			Ref<Texture2D> whiteTexture;

		};

		static SpriteRendererData m_RenderData;

		static SceneData* m_SceneData;

	};
}