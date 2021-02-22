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

			// 对每个字符更新VBO
			float vert[30] = {
				xpos,     ypos + h, pos.z,  0.0, 0.0 ,
				xpos,     ypos,     pos.z,  0.0, 1.0 ,
				xpos + w, ypos,     pos.z,  1.0, 1.0 ,

				xpos,     ypos + h, pos.z,  0.0, 0.0 ,
				xpos + w, ypos,     pos.z,  1.0, 1.0 ,
				xpos + w, ypos + h, pos.z,  1.0, 0.0 
			};

			//  bind texture
			ch.texture->Bind(textNumbers);
			shader->SetSampler2D("_textTexture", textNumbers);
			//textNumbers++;

			text->GetVertexArray()->Bind();

			//  draw sub vertex buffer
			text->GetVertexBuffer()->SetData(vert, sizeof(float) * 30);
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