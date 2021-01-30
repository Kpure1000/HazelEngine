#include "hzpch.h"

#include <glad/glad.h>

#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Log.h"
#include "Platform/Windows/WindowsWindow.h"

using std::shared_ptr;
using std::unique_ptr;

namespace hazel
{
	shared_ptr<Application> Application::m_Instance = nullptr;

	Application::Application()
		: m_IsRunning(false)
	{
		Log::AssertCore(!m_Instance, "Application already exists.");
		m_Instance = shared_ptr<Application>(this);

		m_Window = Window::Create(WindowProps());
		m_Window->SetEventCallback(HZ_BIND_EVENT_FN(OnEvent));
		m_IsRunning = true;
	}

	Application::~Application()
	{

	}

	void Application::OnEvent(Event& ev)
	{
		auto cate = ev.GetEventType();

		Log::InfoCore(ev.ToString());

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			--it;
			(*it)->OnEvent(ev);
			if (ev.Handled)
				break;
		}

		switch (cate)
		{
		case hazel::EventType::WindowClose:
			break;
		case hazel::EventType::WindowResize:
			break;
		case hazel::EventType::WindowFocus:
			break;
		case hazel::EventType::WindowLostFocus:
			break;
		case hazel::EventType::WindowMoved:
			break;
		case hazel::EventType::AppTick:
			break;
		case hazel::EventType::AppUpdate:
			break;
		case hazel::EventType::AppRender:
			break;
		case hazel::EventType::KeyPressed:
			break;
		case hazel::EventType::KeyReleased:
			break;
		case hazel::EventType::KeyTyped:
			break;
		case hazel::EventType::MouseButtonPressed:
			break;
		case hazel::EventType::MouseButtonReleased:
			break;
		case hazel::EventType::MouseMoved:
			break;
		case hazel::EventType::MouseScrolled:
			break;
		default:
			break;
		}
	}

	void Application::PushLayer(std::shared_ptr<Layer> layer)
	{
		m_LayerStack.PuahsLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverLayer(std::shared_ptr<Layer> overLay)
	{
		m_LayerStack.PushOverLay(overLay);
		overLay->OnAttach();
	}

	void Application::Run()
	{
		while (m_IsRunning)
		{
			glClearColor(0.5f, 0.8f, 0.5f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			for (auto layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			m_Window->OnUpdate();
		}
	}

}