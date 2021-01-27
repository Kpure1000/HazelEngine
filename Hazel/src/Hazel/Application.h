#pragma once

#include"Core.h"

#include<memory>
using std::shared_ptr;
using std::make_shared;

namespace hazel
{
	class HAZEL_API Application
	{
	public:

		Application();

		~Application();

		void Run();

	};

	shared_ptr<Application> CreateApplication();
}