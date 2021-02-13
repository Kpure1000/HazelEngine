#pragma once
#include "Window.h"
#include "LayerStack.h"

#include "Events/KeyEvent.h"
#include "Events/ApplicationEvent.h"

#include "ImGui/ImGuiLayer.h"

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

		void PushLayer(Ref<Layer> layer);
		void PushOverLayer(Ref<Layer> overLay);

		inline Window& GetWindow() { return *m_Window; }

		inline void Close() { m_IsRunning = false; }

	private:
		std::unique_ptr<Window> m_Window;
		Ref<ImGuiLayer> m_ImGuiLayer;

		LayerStack m_LayerStack;

		bool m_IsRunning;

	private:
		//  Singleton
		static Application* m_Instance;

	};

	Ref<Application> CreateApplication();

}

#ifndef GetRenderWindow
	#define GetRenderWindow(winType) static_cast<winType*>(Application::GetInstance()\
->GetWindow().GetNativeWindow())
#endif // !GetRenderWindow
