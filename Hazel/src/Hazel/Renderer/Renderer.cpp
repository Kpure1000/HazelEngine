#include "hzpch.h"

#include "Renderer.h"

namespace hazel
{
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::Init()
	{
		RenderCommand::Init();
	}
	
	void Renderer::OnWindowResize(int width, int height)
	{
		RenderCommand::SetViewPort(0, 0, width, height);
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->ViewProjectMat = camera.GetViewProjectMat();
	}
	
	void Renderer::EndScene()
	{
	}
	
	void Renderer::Submit(const Ref<VertexArray>& vertexArray,
		const Ref<Shader>& shader)
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer::Submit(const Ref<Mesh>& mesh,
		const Ref<Shader>& shader)
	{
		shader->Use();
		shader->SetMatrix4("_model", mesh->GetTransform().GetTransMat());
		shader->SetMatrix4("_view_prj", m_SceneData->ViewProjectMat);

		mesh->m_VertexArray->Bind();
		RenderCommand::DrawIndexed(mesh->m_VertexArray);
	}
}