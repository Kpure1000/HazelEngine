#pragma once

#include <sstream>
#include <functional>

#include "Hazel/Events/Event.h"

using std::string;
using std::unique_ptr;

namespace hazel
{
	struct WindowProps
	{
		string title;
		uint32_t width;
		uint32_t height;

		bool isFullScreen;

		WindowProps(const string& Title = "Hazel Engine",
			uint32_t Width = 800, uint32_t Height = 600, bool FullScreen = false)
			: title(Title), width(Width), height(Height), isFullScreen(FullScreen)
		{}

	};

	class HAZEL_API Window
	{
	public:

		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static unique_ptr<Window> Create(const WindowProps& props = WindowProps());

	private:

	};

}
