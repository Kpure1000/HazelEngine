#include "Application.h"

#include "Log.h"
#include "Events/ApplicationEvent.h"

#include <iostream>
#include <thread>

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
		WindowResizeEvent e(800, 600);
		HZ_CORE_TRACE(e);
		int run_frame = 0;
		while (true)
		{
			printf("Running frames count: %d\n", run_frame);
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			run_frame++;
		}
	}

}