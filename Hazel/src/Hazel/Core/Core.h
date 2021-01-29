#pragma once

#pragma warning (disable : 4251)

#ifdef HZ_PLATFORM_WINDOWS
	#ifdef HZ_BUILD_DLL
		#define HAZEL_API __declspec(dllexport)
	#else
		#define HAZEL_API __declspec(dllimport)
	#endif 
#else
	#error Hazel only support Windows
#endif // HZ_PLATFORM_WINDOWS

#define BIT(x) (1 << x)

#if (defined HZ_DEBUG)
	#define HZ_ENABLE_ASSERT
#endif // (defined HZ_DEBUG)

#define HZ_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) \
{ return this->fn(std::forward<decltype(args)>(args)...); }