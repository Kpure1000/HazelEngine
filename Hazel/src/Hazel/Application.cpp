#include "hzpch.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Application.h"

#include "Events/KeyEvent.h"
#include "Log.h"
#include "Platform/Windows/WindowsWindow.h"

using std::shared_ptr;
using std::unique_ptr;

namespace hazel
{
	Application* Application::m_Instance = nullptr;

	Application::Application()
		: m_IsRunning(false)
	{
		Log::AssertCore(!m_Instance, "Application already exists.");
		m_Instance = this;

		m_Window = Window::Create(WindowProps());
		m_Window->SetEventCallback(HZ_BIND_EVENT_FN(OnEvent));
		m_IsRunning = true;
	}

	bool Application::OnWindowClose(WindowCloseEvent& ev)
	{
		m_IsRunning = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& ev)
	{
		glViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());
		return false;
	}

	Application::~Application()
	{
		Log::DebugCore("Application discontruct.");
	}

	void Application::OnEvent(Event& ev)
	{
		EventDispatcher dispatcher(ev);
		dispatcher.Dispatch<WindowCloseEvent>(HZ_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			--it;
			(*it)->OnEvent(ev);
			if (ev.Handled)
				break;
		}

		Log::InfoCore("App Event: {0}", ev.ToString());
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