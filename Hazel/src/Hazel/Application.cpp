#include "hzpch.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Application.h"

#include "Log.h"

#include "Platform/Windows/WindowsWindow.h"
#include "Platform/Windows/WindowsInput.h"


#include "Hazel/Time.h"

using std::shared_ptr;
using std::unique_ptr;

namespace hazel
{
	Application* Application::m_Instance = nullptr;

	Application::Application()
		: m_IsRunning(false)
	{
		//  
		Log::AssertCore(!m_Instance, "Application already exists.");
		m_Instance = this;

		//  create window
		m_Window = Window::Create(WindowProps("Hazel Engine", 800, 800));
		m_Window->SetEventCallback(HZ_BIND_EVENT_FN(OnEvent));

		//  create render layer
		m_RenderLayer = std::make_shared<RenderLayer>();
		PushOverLayer(m_RenderLayer);
		//  create imgui layer
		m_ImGuiLayer = std::make_shared<ImGuiLayer>();
		PushOverLayer(m_ImGuiLayer);

		m_IsRunning = true;
	}

	bool Application::OnWindowClose(WindowCloseEvent& ev)
	{
		m_IsRunning = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& ev)
	{
		glViewport(0, 0, (unsigned int)m_Window->GetSize().x, (unsigned int)m_Window->GetSize().y);
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
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverLayer(std::shared_ptr<Layer> overLay)
	{
		m_LayerStack.PushOverLay(overLay);
		overLay->OnAttach();
	}

	void Application::Run()
	{
		Time::Begin();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_DEPTH_TEST);

		while (m_IsRunning)
		{
			glClearColor(0.5f, 0.6f, 0.5f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//  update all layer
			for (auto layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			//  update ImGui
			m_ImGuiLayer->Begin();
			for (auto layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			//  update window
			m_Window->OnUpdate();
			Time::Update();
		}
	}

}