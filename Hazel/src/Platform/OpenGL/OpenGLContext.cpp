#include "hzpch.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "OpenGLContext.h"

#include "Hazel/Log.h"

hazel::OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
	:m_WindowHandle(windowHandle)
{
}

void hazel::OpenGLContext::Init()
{
	glfwMakeContextCurrent(m_WindowHandle);
	Log::AssertCore((0 != gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)), "Failed to initialize GLAD");

}

void hazel::OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(m_WindowHandle);
}
