#include "RenderLayer.h"

RenderLayer::RenderLayer()
	:m_CameraController((float)Application::GetInstance()->GetWindow().GetSize().x
		/ (float)Application::GetInstance()->GetWindow().GetSize().y, false, true)
{
	//  TODO: 
	//  1. Render a 2D asteroid belt?



}

void RenderLayer::OnAttach()
{
}

void RenderLayer::OnDetch()
{
}

void RenderLayer::OnUpdate()
{
	RenderCommand::Clear();
	RenderCommand::SetClearColor({ 0.3f,0.5f,0.7f,1.0f });

	Renderer::BeginScene(m_CameraController.GetCamera());

	Renderer::EndScene();

}

void RenderLayer::OnImGuiRender()
{
	HZ_PROFILE_FUNCTION();

	ImGui::Begin("Profile");
	//  TODO
	ImGui::End();
}

void RenderLayer::OnEvent(Event& e)
{
}
