#include "hzpch.h"

#include "Hazel/Log.h"

#include "Renderer.h"
#include "VertexArray.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace hazel
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case hazel::RendererAPI::API::None: {
			Log::AssertCore(false, "Renderer API: None is currently not supported.");
			return nullptr;
			break;
		}
		case hazel::RendererAPI::API::OpenGL: {
			return new OpenGLVertexArray();
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