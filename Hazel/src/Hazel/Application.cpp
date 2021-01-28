#include "hzpch.h"
#include "Application.h"
#include "Log.h"
#include "Events/ApplicationEvent.h"
#include "Platform/Windows/WindowsWindow.h"

using std::shared_ptr;
using std::make_shared;

namespace hazel
{

	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		shared_ptr<WindowsWindow> AppWindow = make_shared<WindowsWindow>(WindowProps());
		AppWindow->SetEventCallback([](Event& ev)
			{
				auto cate = ev.GetCategoryFlags();
				Log::DebugCore("log: {0}", ev.ToString());
				switch (static_cast<EventCategory>(cate))
				{
				case EventCategory::EventCategoryApplication :

					break;
				case EventCategory::EventCategoryInput :

					break;
				case EventCategory::EventCategoryKeyboard :

					break;
				case EventCategory::EventCategoryMouse :

					break;
				case EventCategory::EventCategoryMouseButton:

					break;
				default:

					break;
				}
			});
		while (AppWindow->isOpen())
		{
			if (glfwGetKey((GLFWwindow*)AppWindow->GetNativeWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
				AppWindow->Close();

			AppWindow->OnUpdate();

			AppWindow->Display();
		}
	}

}