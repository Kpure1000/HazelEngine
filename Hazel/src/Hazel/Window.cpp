#include "hzpch.h"
#include "Window.h"


#ifdef HZ_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsWindow.h"
#endif

using std::make_shared;
namespace hazel
{
	shared_ptr<Window> hazel::Window::Create(const WindowProps& props)
	{
#ifdef HZ_PLATFORM_WINDOWS
		return make_shared<WindowsWindow>(props);
#else
		Log::CoreError(false, "Unknown platform!");
		return nullptr;
#endif
	}

}