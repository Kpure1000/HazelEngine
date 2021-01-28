#pragma once

#ifdef HZ_PLATFORM_WINDOWS

extern shared_ptr<hazel::Application> hazel::CreateApplication();

int main(int argc, char** argv)
{
	hazel::Log::Init();
#ifdef HZ_DEBUG
	hazel::Log::DebugCore("Debugging:  start.");
#elif HZ_RELEASE
	hazel::Log::InfoCore("Releasing:  start.");
#endif

	auto App = hazel::CreateApplication();
	App->Run();
}

#endif // HZ_PLATFORM_WINDOWS
