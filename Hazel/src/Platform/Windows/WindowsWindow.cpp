#include "hzpch.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "WindowsWindow.h"

#include "Hazel/Log.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/MouseEvent.h"

namespace hazel
{

	static uint32_t m_GLFWWindowCount = 0;

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.title = props.title;
		m_Data.width = props.width;
		m_Data.height = props.height;
		m_Data.isFullScreen = props.isFullScreen;

		if (m_GLFWWindowCount == 0)
		{
			int success = glfwInit();
			Log::AssertCore(success, "Could not initialize GLFW!");

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			m_GLFWWindowCount++;
		}

		int monitorCount;
		auto monitor = glfwGetMonitors(&monitorCount);
		if (monitorCount > 0)
		{
			m_pVideoMode = (GLFWvidmode*)glfwGetVideoMode(monitor[0]);
			m_monitors.reserve(monitorCount);
			m_monitors.assign(monitor, monitor + monitorCount);
		}

		if (m_Data.isFullScreen)
		{
			m_Data.width = m_pVideoMode->width;
			m_Data.height = m_pVideoMode->height;
			//  Use the size of primary monitor
			m_Window = glfwCreateWindow(m_pVideoMode->width, m_pVideoMode->height, m_Data.title.c_str(),
				m_monitors[0], NULL);
		}
		else
		{
			m_Window = glfwCreateWindow((int)m_Data.width, (int)m_Data.height, m_Data.title.c_str(),
				NULL, NULL);
		}


		if (m_Window == NULL)
		{
			std::cerr << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
		}
		else
		{
			glfwMakeContextCurrent(m_Window);

			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				std::cerr << "Failed to initialize GLAD" << std::endl;
			}

			glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
				{
					glViewport(0, 0, width, height);
				});

			// Set GLFW callbacks
			glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
				{
					WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
					data.width = width;
					data.height = height;

					WindowResizeEvent event(width, height);
					data.EventCallback(event);
				});

			glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
				{
					WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
					WindowCloseEvent event;
					data.EventCallback(event);
				});

			glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
				{
					WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

					switch (action)
					{
					case GLFW_PRESS:
					{
						KeyPressedEvent event(key, 0);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event(key);
						data.EventCallback(event);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent event(key, 1);
						data.EventCallback(event);
						break;
					}
					}
				});

			glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
				{
					WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

					KeyTypedEvent event(keycode);
					data.EventCallback(event);
				});

			glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
				{
					WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

					switch (action)
					{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event(button);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event(button);
						data.EventCallback(event);
						break;
					}
					}
				});

			glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
				{
					WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

					MouseScrolledEvent event((float)xOffset, (float)yOffset);
					data.EventCallback(event);
				});

			glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
				{
					WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

					MouseMovedEvent event((float)xPos, (float)yPos);
					data.EventCallback(event);
				});

			glfwSetWindowUserPointer(m_Window, &m_Data);

			glViewport(0, 0, (int)m_Data.width, (int)m_Data.height);

		}

		SetVSync(true);
	}

	void WindowsWindow::Shutdown()
	{
		//glfwSetWindowShouldClose(m_Window, true);
		glfwDestroyWindow(m_Window);
		--m_GLFWWindowCount;

		if (m_GLFWWindowCount == 0)
		{
			glfwTerminate();
		}
	}

}