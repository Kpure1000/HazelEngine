#pragma once

#include "Hazel/Core/Core.h"
#include "RenderCommand.h"

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
			const Transform& trans, const Shader& shader);

		static void Submit(const Text& text,
			const Transform& trans, const Shader& shader);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectMat;
			glm::mat4 ProjectMat;
		};

		static SceneData* m_SceneData;
	};
}