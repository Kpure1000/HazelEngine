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

		Application();

		~Application();

		void Run();

		void OnEvent(Event& ev);

		void PushLayer(std::shared_ptr<Layer> layer);
		void PushOverLayer(std::shared_ptr<Layer> overLay);

	private:
		std::unique_ptr<Window> m_Window;

		LayerStack m_LayerStack;

		bool m_IsRunning;
		
	};

	std::shared_ptr<Application> CreateApplication();

}