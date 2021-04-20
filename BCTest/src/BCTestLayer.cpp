#include "BCTestLayer.h"



#include<imgui.h>


BCTestLayer::BCTestLayer()
{
}

void BCTestLayer::OnAttach()
{
}

void BCTestLayer::OnDetch()
{
}

void BCTestLayer::OnUpdate()
{
	static int count = 0;
	Log::Info("BCTest: {0}.", count++);
}

void BCTestLayer::OnImGuiRender()
{
	HZ_PROFILE_FUNCTION();
	ImGui::Begin("BCTest Properties");
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

void BCTestLayer::OnEvent(Event& e)
{
}
