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

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Sprite& sprite,
			Transform& trans, const Shader& shader);

		static void Submit(const Text& text,
			Transform& trans, const Shader& shader);

		inline static void EnableBatch(bool enable) { m_isBatch = enable; }

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:

		static SceneData* m_SceneData;

		static bool m_isBatch;
	};
}