#include "hzpch.h"

#include "Window.h"
#include "Hazel/Debug/Instrumentor.h"

#ifdef HZ_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsWindow.h"
#endif
using std::make_unique;
namespace hazel
{
	unique_ptr<Window> hazel::Window::Create(const WindowProps& props)
	{
		HZ_PROFILE_FUNCTION();
#ifdef HZ_PLATFORM_WINDOWS
		return make_unique<WindowsWindow>(props);
#else
		Log::CoreError(false, "Unknown platform!");
		return nullptr;
#endif
	}

}