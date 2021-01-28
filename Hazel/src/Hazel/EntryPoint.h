#pragma once

#ifdef HZ_PLATFORM_WINDOWS

extern shared_ptr<hazel::Application> hazel::CreateApplication();

int main(int argc, char** argv)
{
	hazel::Log::Init();
#ifdef HZ_DEBUG
	hazel::Log::ErrorCore("Debugging:  system loading...");
#elif HZ_RELEASE
	hazel::Log::ErrorCore("Releasing:  system loading...");
#elif HZ_DIST
	hazel::Log::ErrorCore("Distributing: system loading...");
#endif
	hazel::Log::Trace("value = {0}+{0}...",0);


	auto App = hazel::CreateApplication();
	App->Run();
}

#endif // HZ_PLATFORM_WINDOWS
