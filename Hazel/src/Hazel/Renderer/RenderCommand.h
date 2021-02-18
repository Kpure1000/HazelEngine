#pragma once

#include "RendererAPI.h"

namespace hazel
{
	/// <summary>
	/// RendererCommand, DO NOT execute multiple command
	/// </summary>
	class RenderCommand
	{
	public:
		inline static void Init()
		{
			m_RendererAPI->Init();
		}

		inline static void SetViewPort(int x, int y, int width, int height)
		{
			m_RendererAPI->SetViewPort(0, 0, width, height);
		}

		inline static void SetClearColor(const glm::vec4& color)
		{
			m_RendererAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			m_RendererAPI->Clear();
		}

		inline static void DrawBuffered(const Ref<VertexArray>& vertexArray)
		{
			m_RendererAPI->DrawBuffered(vertexArray);
		}

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray)
		{
			m_RendererAPI->DrawIndexed(vertexArray);
		}
	private:
		static RendererAPI* m_RendererAPI;
	};
}