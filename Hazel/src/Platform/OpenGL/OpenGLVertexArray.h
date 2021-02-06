#pragma once

#include "Hazel/Core/Core.h"

#include "Hazel/Renderer/VertexArray.h"

namespace hazel
{
	class HAZEL_API OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();

		virtual ~OpenGLVertexArray() override;

		virtual void Bind() const override;

		virtual void UnBind() const override;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vbo) override;

		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& ebo) override;

		inline virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }

		inline virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }

	private:

		unsigned int m_VAO;

		unsigned int m_VertexBufferIndex;

		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};
}

