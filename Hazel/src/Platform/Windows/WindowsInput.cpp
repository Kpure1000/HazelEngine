#include "hzpch.h"

#include "WindowsInput.h"

#include "Hazel/Application.h"

#include <GLFW/glfw3.h>

namespace hazel
{
	Ref<Input> Input::m_Instance = std::make_shared<WindowsInput>();

	bool WindowsInput::IsKeyPressedImpl(KeyCode keyCode)
	{
		auto state = glfwGetKey(GetRenderWindow(GLFWwindow), keyCode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(MouseCode mCode)
	{
		auto state = glfwGetMouseButton(GetRenderWindow(GLFWwindow), mCode);
		return false;
	}

	float WindowsInput::GetMousePosXImpl()
	{
		auto [x, y] = GetMousePosImpl();
		return x;
	}

	float WindowsInput::GetMousePosYImpl()
	{
		auto [x, y] = GetMousePosImpl();
		return y;
	}

	std::pair<float, float> WindowsInput::GetMousePosImpl()
	{
		double x, y;
		glfwGetCursorPos(GetRenderWindow(GLFWwindow), &x, &y);
		return std::pair<float, float>(static_cast<float>(x), static_cast<float>(y));
	}

	float WindowsInput::GetMouseWheelHImpl()
	{
		return 0.0f;
	}

	float WindowsInput::GetMouseWheelVImpl()
	{
		return 0.0f;
	}
}