#pragma once

#include "Hazel/Renderer/RendererAPI.h"

namespace hazel
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;

		virtual void SetViewPort(int x, int y, int width, int height) override;

		virtual void SetClearColor(const glm::vec4& color) override;
		
		virtual void Clear() override;

		virtual void DrawBuffered(const Ref<VertexArray>& vertexArray)override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, size_t indexCount) override;

	};

}
