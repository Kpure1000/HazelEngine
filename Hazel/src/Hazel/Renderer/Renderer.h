#pragma once

#include "Hazel/Core/Core.h"
#include "RenderCommand.h"

#include "Hazel/Graphics/Mesh/Mesh.h"

namespace hazel
{
	/// <summary>
	/// Renderer 
	/// </summary>
	class HAZEL_API Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		static void Submit(const std::shared_ptr<Mesh>& mesh);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	};

}