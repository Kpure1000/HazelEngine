#include "hzpch.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Application.h"

#include "Log.h"

#include "Platform/Windows/WindowsWindow.h"

#include "Time.h"
#include "Hazel/Debug/Instrumentor.h"

#include "Hazel/Renderer/Renderer.h"
#include "Hazel/Renderer/SpriteRenderer.h"

using std::unique_ptr;

namespace hazel
{
	Application* Application::m_Instance = nullptr;

	Application::Application()
		: m_IsRunning(false)
	{
		HZ_PROFILE_BEGIN_SESSION("Hazel Application", "profile_results.json");

		HZ_PROFILE_FUNCTION();
		//  
		Log::AssertCore(!m_Instance, "Application already exists.");
		m_Instance = this;

		//  create window
		m_Window = Window::Create(WindowProps("Hazel Engine", 568, 1024, true, false));
		m_Window->SetEventCallback(HZ_BIND_EVENT_FN(OnEvent));
		//m_Window->SetVSync(false);
		
		//  create imgui layer
		m_ImGuiLayer = std::make_shared<ImGuiLayer>();
		PushOverLayer(m_ImGuiLayer);

		m_IsRunning = true;

		SpriteRenderer::Init();
	}

	Application::~Application()
	{
		HZ_PROFILE_END_SESSION();

		SpriteRenderer::Shutdown();
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
				Renderer::OnWindowResize(app->GetWindow().GetSize().x, app->GetWindow().GetSize().y);
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

		//Log::DebugCore("Application Event: {0}", ev.ToString());
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

		while (m_IsRunning)
		{
			{
				HZ_PROFILE_FUNCTION();

				{
					HZ_PROFILE_SCOPE("Layer Update");
					//  update all layer
					for (auto layer : m_LayerStack)
					{
						layer->OnUpdate();
					}
				}

				{
					HZ_PROFILE_SCOPE("ImGui Update");
					//  update ImGui
					m_ImGuiLayer->Begin();
					for (auto layer : m_LayerStack)
					{
						layer->OnImGuiRender();
					}
					m_ImGuiLayer->End();
				}

				{
					HZ_PROFILE_SCOPE("Window Update");
					//  update window
					m_Window->OnUpdate();
				}
				Time::Update();
			}
		}
	}

}