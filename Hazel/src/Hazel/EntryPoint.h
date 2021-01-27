#pragma once

#ifdef HZ_PLATFORM_WINDOWS

extern shared_ptr<hazel::Application> hazel::CreateApplication();

int main(int argc, char** argv)
{
	auto App = hazel::CreateApplication();
	App->Run();
}

#endif // HZ_PLATFORM_WINDOWS
