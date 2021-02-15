#pragma once

#include "Hazel/Core/Core.h"
#include "RenderCommand.h"

#include "Hazel/Graphics/Transform.h"
#include "Hazel/Renderer/Shader.h"
#include "Hazel/Graphics/Mesh/Mesh.h"
#include "Hazel/Renderer/Camera/OrthographicCamera.h"

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
			const Ref<Transform> trans, const Ref<Shader>& shader);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
		
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectMat;
		};

		static SceneData* m_SceneData;

	};

}