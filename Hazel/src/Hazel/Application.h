#pragma once
#include"Core/Core.h"

#include <memory>
using std::shared_ptr;


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