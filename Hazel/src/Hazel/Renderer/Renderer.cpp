#include "hzpch.h"

#include "Renderer.h"
#include "Hazel/Debug/Instrumentor.h"

namespace hazel
{
	SceneData* Renderer::m_SceneData = new SceneData;

	void Renderer::Init()
	{
		HZ_PROFILE_FUNCTION();
		RenderCommand::Init();
	}
	
	void Renderer::OnWindowResize(int width, int height)
	{
		RenderCommand::SetViewPort(0, 0, width, height);
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->ViewProjectMat = camera.GetViewProjectMat();
		m_SceneData->ProjectMat = camera.GetProjectMat();
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
		const Ref<Transform>& trans, const Ref<Shader>& shader)
	{
		shader->Use();
		shader->SetMatrix4("_model", trans->GetTransMat());
		shader->SetMatrix4("_view_prj", m_SceneData->ViewProjectMat);

		mesh->GetVertexArray()->Bind();
		RenderCommand::DrawIndexed(mesh->GetVertexArray());
	}

	void Renderer::Submit(Mesh* mesh,
		Transform* trans, const Ref<Shader>& shader)
	{
		shader->Use();
		shader->SetMatrix4("_model", trans->GetTransMat());
		shader->SetMatrix4("_view_prj", m_SceneData->ViewProjectMat);

		mesh->GetVertexArray()->Bind();
		RenderCommand::DrawIndexed(mesh->GetVertexArray());
	}

	void Renderer::Submit(const Ref<Text>& text, const Ref<Transform>& trans, const Ref<Shader>& shader)
	{
		shader->Use();
		shader->SetMatrix4("_projection", m_SceneData->ProjectMat);
		shader->SetVector4("_textColor", text->GetColor());

		auto& content = text->GetText();
		auto characters = text->GetCharacters();
		auto scale = trans->GetScale();

		int textNumbers = 0;
		auto pos = trans->GetPosition();
		for (auto chStr : content)
		{
			Character ch = characters[chStr];

			if (chStr == '\n')
			{
				pos.y -= (ch.size.y << 1) * scale.y;
				pos.x = trans->GetPosition().x;
				continue;
			}

			float xpos = pos.x + ch.bearing.x * scale.x;
			float ypos = pos.y - (ch.size.y - ch.bearing.y) * scale.y;

			float w = ch.size.x * scale.x;
			float h = ch.size.y * scale.y;

			float vert[18] = {
				xpos,     ypos + h, pos.z,
				xpos,     ypos,     pos.z,
				xpos + w, ypos,     pos.z,

				xpos,     ypos + h, pos.z,
				xpos + w, ypos,     pos.z,
				xpos + w, ypos + h, pos.z
			};
			float texC[12] = {
				0.0, 0.0,
				0.0, 1.0,
				1.0, 1.0,

				0.0, 0.0,
				1.0, 1.0,
				1.0, 0.0
			};

			//  bind texture
			ch.texture->Bind(textNumbers);
			shader->SetSampler2D("_textTexture", textNumbers);
			//textNumbers++;

			text->GetVertexArray()->Bind();

			//  draw sub vertex buffer
			text->GetVertexBuffer_Vertex()->SetData(vert, sizeof(float) * 18);

			text->GetVertexBuffer_TexCoord()->SetData(texC, sizeof(float) * 12);

			RenderCommand::DrawBuffered(text->GetVertexArray());

			//  or draw sub index buffer
			/*unsigned int indi[6] = {
				0,1,2,
				5,4,3
			};*/
			//text->GetIndexBuffer()->SetData(indi, 6);
			//RenderCommand::DrawIndexed(text->GetVertexArray());

			//  offset 2^6 
			pos.x += (ch.advance >> 6) * scale.x;
		}

	}

}