#pragma once
#include "Window.h"
#include "LayerStack.h"

#include "Events/KeyEvent.h"
#include "Events/ApplicationEvent.h"

#include "ImGui/ImGuiLayer.h"
#include "Hazel/Renderer/RenderLayer.h"

#include "Hazel/Utility/Singleton.h"

namespace hazel
{
	class HAZEL_API Application
	{
	public:

		inline static Application* GetInstance() { return m_Instance; }

		Application();
		~Application();

		void Run();

		void OnEvent(Event& ev);

		void PushLayer(std::shared_ptr<Layer> layer);
		void PushOverLayer(std::shared_ptr<Layer> overLay);

		inline Window& GetWindow() { return *m_Window; }

	private:
		std::unique_ptr<Window> m_Window;
		std::shared_ptr<ImGuiLayer> m_ImGuiLayer;
		std::shared_ptr<RenderLayer> m_RenderLayer;

		LayerStack m_LayerStack;

		bool m_IsRunning;

	private:
		//  Singleton
		static Application* m_Instance;

	};

	std::shared_ptr<Application> CreateApplication();

}

#ifndef GetRenderWindow
	#define GetRenderWindow(winType) static_cast<winType*>(Application::GetInstance()\
->GetWindow().GetNativeWindow())
#endif // !GetRenderWindow
