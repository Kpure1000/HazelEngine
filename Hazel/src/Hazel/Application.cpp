#include "hzpch.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Application.h"

#include "Log.h"

#include "Platform/Windows/WindowsWindow.h"

#include "Hazel/Time.h"

#include "Hazel/Renderer/Renderer.h"

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
		m_Window = Window::Create(WindowProps("Hazel Engine", 800, 800, true, false));
		m_Window->SetEventCallback(HZ_BIND_EVENT_FN(OnEvent));

		//  create imgui layer
		m_ImGuiLayer = std::make_shared<ImGuiLayer>();
		PushOverLayer(m_ImGuiLayer);

		m_IsRunning = true;
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event& ev)
	{
		EventDispatcher dispatcher(ev);
		dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& ev)
			{
				m_IsRunning = false;
				return true;
			});
		dispatcher.Dispatch<WindowResizeEvent>([](WindowResizeEvent& ev)
			{
				auto app = Application::GetInstance();
				glViewport(0, 0, (unsigned int)app->GetWindow().GetSize().x,
					(unsigned int)app->GetWindow().GetSize().y);
				return false;
			});

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			--it;
			(*it)->OnEvent(ev);
			if (ev.Handled)
			{
				//  if event handled, throw it
				break;
			}
		}

		Log::InfoCore("App Event: {0}", ev.ToString());
	}

	void Application::PushLayer(Ref<Layer> layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverLayer(Ref<Layer> overLay)
	{
		m_LayerStack.PushOverLay(overLay);
		overLay->OnAttach();
	}

	void Application::Run()
	{
		Time::Begin();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);

		while (m_IsRunning)
		{
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