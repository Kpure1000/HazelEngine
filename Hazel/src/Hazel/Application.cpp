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
		Log::Trace(e);
		int run_frame = 0;
		while (true)
		{
			Log::Trace("Running frames count: {0}", run_frame);
			run_frame++;

			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
	}

}