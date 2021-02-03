//#pragma warning (disable:4005)
#include <Hazel.h>

#include <imgui.h>
using std::shared_ptr;
using std::make_shared;
using namespace hazel;

class ExampleLayer : public hazel::Layer
{

public:
	ExampleLayer()
		: Layer("Eaxample")
	{
	}

	void OnUpdate() override
	{
		
	}

	void OnImGuiRender() override
	{
		//  Missing dear imgui context. Refer to examples app!
		/*bool show = true;
		ImGui::Begin("State", &show);
		ImGui::Text("Welcome to Hazel Engine!");
		ImGui::End();*/
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