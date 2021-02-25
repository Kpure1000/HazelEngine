#include "hzpch.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "OpenGLContext.h"

#include "Hazel/Core/Log.h"
#include "Hazel/Debug/Instrumentor.h"

hazel::OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
	:m_WindowHandle(windowHandle)
{
}

void hazel::OpenGLContext::Init()
{
	HZ_PROFILE_FUNCTION();

	glfwMakeContextCurrent(m_WindowHandle);
	Log::AssertCore((0 != gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)), "Failed to initialize GLAD");

	Log::InfoCore("\n>>>OpenGL Info>>>\n>Version:\t{0}\n\
>Vender:\t{1}\n>Renderer:\t{2}\n>>>>>>>>>>>>>>>>>",
		glGetString(GL_VERSION), glGetString(GL_VENDOR), glGetString(GL_RENDERER));
}

void hazel::OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(m_WindowHandle);
}
