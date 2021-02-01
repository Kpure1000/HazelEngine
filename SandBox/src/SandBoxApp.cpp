#include <Hazel.h>

#include <imgui.h>
#include <Hazel/ImGui/ImGuiLayer.h>

using std::shared_ptr;
using std::make_shared;
using hazel::Log;

class ExampleLayer : public hazel::Layer
{
public:
	ExampleLayer()
		: Layer("Eaxample")
	{

	}

	void OnUpdate() override
	{
		//Log::Trace("ExampleLayer Update");
	}

	void OnImGuiRender() override
	{
		//  Missing dear imgui context. Refer to examples app!
		bool show = true;
		ImGui::Begin("State", &show);
		ImGui::Text("Welcome to Hazel Engine!");
		ImGui::End();
		//  error
	}

	void OnEvent(hazel::Event& ev) override
	{
		Log::Debug("ExampleLayer Event: {0}", ev.ToString());
	}

};

class SandBox : public hazel::Application
{
public:

	SandBox()
	{
		PushLayer(make_shared<ExampleLayer>());
	}

	~SandBox()
	{

	}

};

shared_ptr<hazel::Application> hazel::CreateApplication()
{
	return make_shared<SandBox>();
}