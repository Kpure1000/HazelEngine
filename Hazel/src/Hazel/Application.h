#pragma once
#include "Core/Core.h"
#include "Window.h"
#include "Events/Event.h"
#include "LayerStack.h"

namespace hazel
{
	class HAZEL_API Application
	{
	public:

		inline static std::shared_ptr<Application> GetInstance() { return m_Instance; }

		~Application();

		void Run();

		void OnEvent(Event& ev);

		void PushLayer(std::shared_ptr<Layer> layer);
		void PushOverLayer(std::shared_ptr<Layer> overLay);

		inline Window& GetWindow() { return *m_Window; }

	protected:
		Application();

	private:

		std::unique_ptr<Window> m_Window;

		LayerStack m_LayerStack;

		bool m_IsRunning;

	private:
		//  Singleton

		static std::shared_ptr<Application> m_Instance;

	};

	std::shared_ptr<Application> CreateApplication();

}