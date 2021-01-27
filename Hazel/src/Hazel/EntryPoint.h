#pragma once

#ifdef HZ_PLATFORM_WINDOWS

extern shared_ptr<hazel::Application> hazel::CreateApplication();

int main(int argc, char** argv)
{
	hazel::Log::Init();
#ifdef HZ_DEBUG
	HZ_CORE_ERROR("Debugging:  system loading...");
#elif HZ_RELEASE
	HZ_CORE_ERROR("Releasing:  system loading...");
#elif HZ_DIST
	HZ_CORE_ERROR("Distributing: system loading...");
#endif
	HZ_CLIENT_CRITICAL("value = {0}+{0}...",0);


	auto App = hazel::CreateApplication();
	App->Run();
}

#endif // HZ_PLATFORM_WINDOWS
