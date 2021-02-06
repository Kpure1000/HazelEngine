#include "hzpch.h"

#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace hazel
{
	RendererAPI* RenderCommand::m_RendererAPI = new OpenGLRendererAPI();
}