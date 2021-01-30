#pragma once
#include "Hazel/Window.h"

struct GLFWwindow;
struct GLFWvidmode;
struct GLFWmonitor;

using std::vector;

namespace hazel
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);

		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.width; }
		inline unsigned int GetHeight() const override { return m_Data.height; }

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		inline void SetVSync(bool enabled) override;
		inline bool IsVSync() const override;

		inline virtual void* GetNativeWindow()const { return m_Window; }

	private:

		virtual void Init(const WindowProps& props);

		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;

		GLFWvidmode* m_pVideoMode;

		vector<GLFWmonitor*> m_monitors;
		
		struct WindowData
		{
			std::string title;
			unsigned int width, height;
			bool VSync;
			bool isFullScreen;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;

	};

}