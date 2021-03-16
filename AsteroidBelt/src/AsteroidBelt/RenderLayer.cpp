#include "RenderLayer.h"

RenderLayer::RenderLayer()
	:m_CameraController((float)Application::GetInstance()->GetWindow().GetSize().x
		/ (float)Application::GetInstance()->GetWindow().GetSize().y, false, true)
{
	m_CameraController.EnableInput(true);

	m_Tex.reset(Texture2D::Create());
	m_Tex->LoadFromFile("../data/texture/awesomeface.png");
	m_Sprite = Sprite(m_Tex->GetSize());
}

void RenderLayer::OnAttach()
{
	m_Trans.SetPosition({ 0.0f,1.0f,1.0f });
	m_Trans.SetScale({ 0.1f,0.1f,1.0f });
}

void RenderLayer::OnDetch()
{
}

void RenderLayer::OnUpdate()
{
	m_CameraController.OnUpdate();
	
	RenderCommand::Clear();
	RenderCommand::SetClearColor({ 0.3f,0.5f,0.7f,1.0f });
	
	SpriteRenderer::ResetState();

	SpriteRenderer::BeginScene(m_CameraController.GetCamera());
	float radius = 250.0f;
	for (int i = 0; i < 306; i++) {
		m_Trans.SetPosition({ radius * cos(glm::radians((float)i * 3.6f)),
			radius * sin(glm::radians((float)i * 3.6f)),(float)i });
		SpriteRenderer::Submit(m_Sprite, m_Trans, m_Tex);
	}

	SpriteRenderer::NewBatch();

	SpriteRenderer::EndScene();

}

void RenderLayer::OnImGuiRender()
{
	HZ_PROFILE_FUNCTION();

	ImGui::Begin("Profile");
	//  TODO
	ImGui::Text("DrawCalls: %lld", SpriteRenderer::GetState().DrawCalls);
	ImGui::End();
}

void RenderLayer::OnEvent(Event& e)
{
}
