#pragma once

#ifdef HZ_PLATFORM_WINDOWS
	#ifdef HZ_DYNAMIC_LIB
		#ifdef HZ_BUILD_DLL
			#define HAZEL_API __declspec(dllexport)
		#else
			#define HAZEL_API __declspec(dllimport)
		#endif 
	#else  // HZ_STATIC_LIB
		#define HAZEL_API 
	#endif // HZ_DYNAMIC_LIB
#else
	#error Hazel only support Windows
#endif // HZ_PLATFORM_WINDOWS

#define BIT(x) (1 << x)

#ifdef HZ_DEBUG
	#define HZ_ENABLE_ASSERT
#endif // (defined HZ_DEBUG)

#define HZ_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) \
{ return this->fn(std::forward<decltype(args)>(args)...); }

namespace hazel
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}