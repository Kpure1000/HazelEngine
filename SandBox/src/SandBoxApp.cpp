#include <Hazel.h>

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
		PushOverLayer(make_shared<hazel::ImGuiLayer>());
	}

	~SandBox()
	{

	}

};

shared_ptr<hazel::Application> hazel::CreateApplication()
{
	return make_shared<SandBox>();
}