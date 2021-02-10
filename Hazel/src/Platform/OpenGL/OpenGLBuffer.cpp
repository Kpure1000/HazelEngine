#include "hzpch.h"

#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace hazel
{
	//////////////////////////////////
	// VertexBuffer
	//////////////////////////////////

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, size_t size)
		:m_VBOID(0)
	{
		glGenBuffers(1, &m_VBOID);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBOID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_VBOID);
	}

	void OpenGLVertexBuffer::Bind()const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBOID);
	}

	void OpenGLVertexBuffer::UnBind()const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::SetData(const void* data, size_t size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBOID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

	///////////////////////////////////
	// IndexBuffer
	//////////////////////////////////

	OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int* indices, size_t count)
		: m_EBOID(0), m_Count(count)
	{
		glGenBuffers(1, &m_EBOID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBOID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_EBOID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBOID);
	}

	void OpenGLIndexBuffer::UnBind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}