#pragma once

#include "RenderCommand.h"
#include "RenderData.h"

#include "Hazel/Renderer/Shader.h"
#include "Hazel/Renderer/Camera/OrthographicCamera.h"

#include "Hazel/Graphics/Transform.h"
#include "Hazel/Graphics/Mesh/Mesh.h"
#include "Hazel/Graphics/Text.h"

namespace hazel
{
	/// <summary>
	/// Renderer 
	/// </summary>
	class HAZEL_API Renderer
	{
	public:
		static void Init();

		static void OnWindowResize(int width, int height);
		
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Ref<VertexArray>& vertexArray,
			const Ref<Shader>& shader);

		static void Submit(const Ref<Mesh>& mesh,
			const Ref<Transform>& trans, const Ref<Shader>& shader);
		
		static void Submit(Mesh* mesh,
			Transform* trans, const Ref<Shader>& shader);

		static void Submit(const Ref<Text>& text,
			const Ref<Transform>& trans, const Ref<Shader>& shader);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
		
	private:

		static SceneData* m_SceneData;

	};

}