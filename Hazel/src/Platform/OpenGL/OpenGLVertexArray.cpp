#include "hzpch.h"

#include "Hazel/Log.h"

#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace hazel
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:    return GL_FLOAT;
		case ShaderDataType::Float2:   return GL_FLOAT;
		case ShaderDataType::Float3:   return GL_FLOAT;
		case ShaderDataType::Float4:   return GL_FLOAT;
		case ShaderDataType::Mat3:     return GL_FLOAT;
		case ShaderDataType::Mat4:     return GL_FLOAT;
		case ShaderDataType::Int:      return GL_INT;
		case ShaderDataType::Int2:     return GL_INT;
		case ShaderDataType::Int3:     return GL_INT;
		case ShaderDataType::Int4:     return GL_INT;
		case ShaderDataType::Bool:     return GL_BOOL;
		}
		Log::AssertCore(false, "Unknown ShaderDataType!");
		return 0;
	}
	OpenGLVertexArray::OpenGLVertexArray()
		:m_VertexBufferIndex(0)
	{
		glGenVertexArrays(1, &m_VAO);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_VAO);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_VAO);
	}

	void OpenGLVertexArray::UnBind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vbo)
	{
		Log::AssertCore(0 != vbo->GetLayout().GetElements().size(), "VertexBuffer Layout is empty.");
		glBindVertexArray(m_VAO);
		vbo->Bind();

		const auto& layout = vbo->GetLayout();
		for (const auto& item : layout)
		{
			auto type = item.type;
			switch (type) {
			case hazel::ShaderDataType::Float:
			case hazel::ShaderDataType::Float2: 
			case hazel::ShaderDataType::Float3: 
			case hazel::ShaderDataType::Float4:
			case hazel::ShaderDataType::Int:
			case hazel::ShaderDataType::Int2:
			case hazel::ShaderDataType::Int3:
			case hazel::ShaderDataType::Int4:
			case hazel::ShaderDataType::Bool: {
				glEnableVertexAttribArray(m_VertexBufferIndex);
				glVertexAttribPointer(m_VertexBufferIndex,
					item.GetElementCount(),
					ShaderDataTypeToOpenGLBaseType(item.type),
					item.normalized ? GL_TRUE : GL_FALSE,
					layout.GetStride(),
					(const void*)item.offset
				);
				m_VertexBufferIndex++;
				break;
			}
			case hazel::ShaderDataType::Mat3:
			case hazel::ShaderDataType::Mat4: {
				auto count = item.GetElementCount();
				for (size_t i = 0; i < count; i++) {
					glEnableVertexAttribArray(m_VertexBufferIndex);
					glVertexAttribPointer(m_VertexBufferIndex,
						count,
						ShaderDataTypeToOpenGLBaseType(item.type),
						item.normalized ? GL_TRUE : GL_FALSE,
						layout.GetStride(),
						(const void*)(item.offset + sizeof(float) * count * i)
					);
					glVertexAttribDivisor(m_VertexBufferIndex, 1);
					m_VertexBufferIndex++;
				}
				break;
			}
			default:
				Log::AssertCore(false, "Unknown ShaderDataType");
			}
		}

		m_VertexBuffers.push_back(vbo);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& ebo)
	{
		glBindVertexArray(m_VAO);
		ebo->Bind();

		m_IndexBuffer = ebo;
	}
}
