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

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vbo) override;

		virtual void SetIndexBuffer(const Ref<IndexBuffer>& ebo) override;

		inline virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }

		inline virtual const Ref<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }

	private:

		unsigned int m_VAO;

		unsigned int m_VertexBufferIndex;

		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}

