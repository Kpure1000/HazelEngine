#include "hzpch.h"

#include "Buffer.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace hazel
{
	////////////////////////
	// ShaderDataType
	////////////////////////

	////////////////////////
	// VertexElement
	////////////////////////

	unsigned int BufferElement::GetElementCount() const
	{
		switch (type)
		{
		case hazel::ShaderDataType::None: return 0;
			break;
		case hazel::ShaderDataType::Float: return 1;
			break;
		case hazel::ShaderDataType::Float2: return 2;
			break;
		case hazel::ShaderDataType::Float3: return 3;
			break;
		case hazel::ShaderDataType::Float4: return 4;
			break;
		case hazel::ShaderDataType::Mat3: return 3;
			break;
		case hazel::ShaderDataType::Mat4: return 4;
			break;
		case hazel::ShaderDataType::Int: return 1;
			break;
		case hazel::ShaderDataType::Int2: return 2;
			break;
		case hazel::ShaderDataType::Int3: return 3;
			break;
		case hazel::ShaderDataType::Int4: return 4;
			break;
		case hazel::ShaderDataType::Bool: return 1;
			break;
		}
		return 0;
	}

	////////////////////////
	// VertexBuffer
	////////////////////////

	VertexBuffer* VertexBuffer::Create(float* vertices, size_t size)
	{
		switch (Renderer::GetAPI()) {
		case hazel::RendererAPI::API::None: {
			Log::AssertCore(false, "Renderer API: None is currently not supported.");
			return nullptr;
			break;
		}
		case hazel::RendererAPI::API::OpenGL: {
			return new OpenGLVertexBuffer(vertices, size);
			break;
		}
		case hazel::RendererAPI::API::Direct3D: {
			Log::AssertCore(false, "RendererAPI: Direct3D is coming soon.");
			return nullptr;
			break;
		}
		}
		Log::AssertCore(false, "Unkown Renderer API!");
		return nullptr;
	}

	////////////////////////
	// IndexBuffer
	////////////////////////

	IndexBuffer* IndexBuffer::Create(unsigned int* indices, size_t count)
	{
		switch (Renderer::GetAPI()) {
		case hazel::RendererAPI::API::None: {
			Log::AssertCore(false, "Renderer API: None is currently not supported.");
			return nullptr;
			break;
		}
		case hazel::RendererAPI::API::OpenGL: {
			return new OpenGLIndexBuffer(indices, count);
			break;
		}
		case hazel::RendererAPI::API::Direct3D: {
			Log::AssertCore(false, "RendererAPI: Direct3D is coming soon.");
			return nullptr;
			break;
		}
		}
		Log::AssertCore(false, "Unkown Renderer API!");
		return nullptr;
	}

}