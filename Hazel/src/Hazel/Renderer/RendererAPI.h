#pragma once

#include <glm/glm.hpp>

#include "VertexArray.h"

namespace hazel
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0,
			OpenGL = 1,
			Direct3D
		};
	public:
		virtual void Init() = 0;

		virtual void SetViewPort(int x, int y, int width, int height) = 0;
		
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawBuffered(const Ref<VertexArray>& vertexArray) = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, size_t indexCount) = 0;

		inline static API GetAPI() { return m_API; }

	private:
		static API m_API;

	};
}