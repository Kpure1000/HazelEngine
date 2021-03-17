#include "RenderLayer.h"

RenderLayer::RenderLayer()
	:m_CameraController((float)Application::GetInstance()->GetWindow().GetSize().x
		/ (float)Application::GetInstance()->GetWindow().GetSize().y, false, true)
{
	m_CameraController.EnableInput(true);
	m_CameraController.EnableZoom(true);

	m_Tex.reset(Texture2D::Create());
	m_Tex->LoadFromFile("../data/texture/awesomeface.png");
	m_Sprite = Sprite(m_Tex->GetSize());
}

void RenderLayer::OnAttach()
{
	m_Trans.SetPosition({ 0.0f,1.0f,1.0f });
	m_Trans.SetScale({ 0.05f,0.05f,1.0f });
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
	for (int i = 0; i < 3000; i++) {
		m_Trans.SetPosition({ radius * cos(glm::radians((float)i * 3.6f)),
			radius * sin(glm::radians((float)i * 3.6f)),(float)i });
		SpriteRenderer::Submit(m_Sprite, m_Trans, m_Tex);
	}
	
	SpriteRenderer::EndScene();

}

void RenderLayer::OnImGuiRender()
{
	HZ_PROFILE_FUNCTION();

	ImGui::Begin("Profile");
	//  TODO
	ImGui::Text("%lld DrawCalls", SpriteRenderer::GetState().DrawCalls);
	static float ddt = 400.0f;
	static float framePS = 0.0f;
	ddt += Time::deltaTime();
	if (ddt > 1.0f) {
		framePS = 1.0f / Time::deltaTime();
		ddt = 0.0f;
	}
	ImGui::Text("%f FPS", framePS);
	ImGui::End();
}

void RenderLayer::OnEvent(Event& e)
{
	m_CameraController.OnEvent(e);
	auto evd = EventDispatcher(e);
	evd.Dispatch<KeyPressedEvent>([this](KeyPressedEvent& ev)
		{
			if (ev.GetKeyCode() == Key::Escape)
			{
				Application::GetInstance()->Close();
				return true;
			}
			return false;
		});
}
