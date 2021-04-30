#pragma once

#ifdef KRT_PLATFORM_WINDOWS
	#ifdef KRT_DYNAMIC_LIB
		#ifdef KRT_BUILD_DLL
			#define KRT_API __declspec(dllexport)
		#else
			#define KRT_API __declspec(dllimport)
		#endif 
	#else  // KRT_STATIC_LIB
		#define KRT_API 
	#endif // KRT_DYNAMIC_LIB
#else
	#error KRT only support Windows
#endif // HZ_PLATFORM_WINDOWS

#ifndef BIT
#define BIT(x) (1 << x)
#endif // !BIT

#ifndef TO_RGB
#define TO_RGB 255.99f
#endif // !_TO_RGB

#ifdef KRT_DEBUG
#define KRT_ENABLE_ASSERT
#endif // (defined HZ_DEBUG)

#define KRT_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) \
{ return this->fn(std::forward<decltype(args)>(args)...); }

namespace krt
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}