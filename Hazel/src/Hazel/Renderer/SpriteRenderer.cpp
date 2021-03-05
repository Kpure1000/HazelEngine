#include "hzpch.h"
#include "SpriteRenderer.h"

#include "Hazel/Debug/Instrumentor.h"

namespace hazel
{
	void SpriteRenderer::Init()
	{
		HZ_PROFILE_FUNCTION();
		RenderCommand::Init();
	}
	
	void SpriteRenderer::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->ProjectMat = camera.GetProjectMat();
		m_SceneData->ViewProjectMat= camera.GetViewProjectMat();
	}
	
	void SpriteRenderer::EndScene()
	{
	}
	
	void SpriteRenderer::Submit(const Sprite& sprite, const Transform& trans, const Shader& shader)
	{
		
	}
	
	void SpriteRenderer::Submit(const Text& text, const Transform& trans, const Shader& shader)
	{
		
	}
}