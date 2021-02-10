#include "hzpch.h"

#include "Texture.h"

#include "Platform/OpenGL/OpenGLTexture.h"
#include "Renderer.h"

namespace hazel
{
	Texture2D* Texture2D::Create()
	{
		switch (Renderer::GetAPI()) {
		case hazel::RendererAPI::API::None: {
			Log::AssertCore(false, "Create Texture: Renderer API: None is currently not supported.");
			return nullptr;
			break;
		}
		case hazel::RendererAPI::API::OpenGL: {
			return new OpenGLTexture();
			break;
		}
		case hazel::RendererAPI::API::Direct3D: {
			Log::AssertCore(false, "Create Texture: RendererAPI: Direct3D is coming soon.");
			return nullptr;
			break;
		}
		}
		Log::AssertCore(false, "Create Texture: Unkown Renderer API!");
		return nullptr;
	}

}