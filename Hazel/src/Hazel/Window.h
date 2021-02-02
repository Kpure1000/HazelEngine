#pragma once

#include <sstream>
#include <functional>

#include<glm/glm.hpp>

#include "Hazel/Events/Event.h"

using std::string;
using std::unique_ptr;


namespace hazel
{
	/// <summary>
	/// Properties of window
	/// </summary>
	struct WindowProps
	{
		//  Window title
		string title;

		//  Window size
		glm::vec2 size;

		//  Is window fullscreen
		bool isFullScreen;

		WindowProps(const string& Title = "Hazel Engine",
			uint32_t Width = 800, uint32_t Height = 600, bool FullScreen = false)
			: title(Title), size(Width, Height), isFullScreen(FullScreen)
		{}

	};

	/// <summary>
	/// Window of application
	/// </summary>
	class HAZEL_API Window
	{
	public:

		/// <summary>
		/// Event callback by window
		/// </summary>
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual glm::vec2 GetSize()const = 0;

		/*virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;*/

		/// <summary>
		/// Set the event callback
		/// </summary>
		/// <param name="callback">Event Callback Function</param>
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		/// <summary>
		/// Get the window handle with render context
		/// </summary>
		/// <returns></returns>
		virtual void* GetNativeWindow() const = 0;

		/// <summary>
		/// Create an unique window
		/// </summary>
		/// <param name="props"></param>
		/// <returns></returns>
		static unique_ptr<Window> Create(const WindowProps& props = WindowProps());

	};

}
