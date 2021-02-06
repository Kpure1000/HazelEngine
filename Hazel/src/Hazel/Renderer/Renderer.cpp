#include "hzpch.h"

#include "Renderer.h"

namespace hazel
{
	void Renderer::BeginScene()
	{
	}
	
	void Renderer::EndScene()
	{
	}
	
	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer::Submit(const std::shared_ptr<Mesh>& mesh)
	{
		mesh->m_VertexArray->Bind();
		RenderCommand::DrawIndexed(mesh->m_VertexArray);
	}
}