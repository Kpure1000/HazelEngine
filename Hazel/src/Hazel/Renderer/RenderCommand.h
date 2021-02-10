#pragma once

#include "RendererAPI.h"

namespace hazel
{
	/// <summary>
	/// RendererCommand, DO NOT do multiple command
	/// </summary>
	class RenderCommand
	{
	public:

		inline static void SetClearColor(const glm::vec4& color)
		{
			m_RendererAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			m_RendererAPI->Clear();
		}

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray)
		{
			m_RendererAPI->DrawIndexed(vertexArray);
		}
	private:
		static RendererAPI* m_RendererAPI;
	};
}