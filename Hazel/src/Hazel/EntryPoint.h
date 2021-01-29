#pragma once

#ifdef HZ_PLATFORM_WINDOWS

	extern std::shared_ptr<hazel::Application> hazel::CreateApplication();

	int main(int argc, char** argv)
	{
		//  initialize log system
		hazel::Log::Init();

	#ifdef HZ_DEBUG
		hazel::Log::DebugCore("Debugging:  start.");
	#endif

		//  create application
		auto App = hazel::CreateApplication();

		//  app run start
		App->Run();
	}

#endif // HZ_PLATFORM_WINDOWS
