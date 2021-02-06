#pragma once

#include "Hazel/Renderer/Buffer.h"

namespace hazel
{
	/// <summary>
	/// Vertex Buffer with OpenGL
	/// </summary>
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, size_t size);
		virtual ~OpenGLVertexBuffer() override;

		virtual void Bind()const override;
		virtual void UnBind()const override;

		virtual void SetData(const void* data, size_t size) override;
		inline virtual const BufferLayout& GetLayout() const override { return m_Layout; }
		inline virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
	private:
		unsigned int m_VBOID;

		BufferLayout m_Layout;

	};

	/// <summary>
	/// Index Buffer with OpenGL
	/// </summary>
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(unsigned int* indices, size_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void UnBind() const override;
	
		inline virtual size_t GetCount() override { return m_Count; }

	private:
		unsigned int m_EBOID;

		size_t m_Count;

	};
	
}