#include"hzpch.h"

#include"ImGuiLayer.h"

#include "Hazel/Application.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/MouseEvent.h"
#include "Platform/Windows/WindowsWindow.h"

namespace hazel
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer"), m_Time(0.0f)
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO(); (void)io;

		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
		// Keyboard mapping. ImGui will use those indices to peek into the io.KeysDown[] array.
		io.KeyMap[ImGuiKey_Tab] = Key::Tab;
		io.KeyMap[ImGuiKey_LeftArrow] = Key::Left;
		io.KeyMap[ImGuiKey_RightArrow] = Key::Right;
		io.KeyMap[ImGuiKey_UpArrow] = Key::Up;
		io.KeyMap[ImGuiKey_DownArrow] = Key::Down;
		io.KeyMap[ImGuiKey_PageUp] = Key::PageUp;
		io.KeyMap[ImGuiKey_PageDown] = Key::PageDown;
		io.KeyMap[ImGuiKey_Home] = Key::Home;
		io.KeyMap[ImGuiKey_End] = Key::End;
		io.KeyMap[ImGuiKey_Insert] = Key::Insert;
		io.KeyMap[ImGuiKey_Delete] = Key::Delete;
		io.KeyMap[ImGuiKey_Backspace] = Key::Backspace;
		io.KeyMap[ImGuiKey_Space] = Key::Space;
		io.KeyMap[ImGuiKey_Enter] = Key::Enter;
		io.KeyMap[ImGuiKey_Escape] = Key::Escape;
		io.KeyMap[ImGuiKey_KeyPadEnter] = Key::KPEnter;
		io.KeyMap[ImGuiKey_A] = Key::A;
		io.KeyMap[ImGuiKey_C] = Key::C;
		io.KeyMap[ImGuiKey_V] = Key::V;
		io.KeyMap[ImGuiKey_X] = Key::X;
		io.KeyMap[ImGuiKey_Y] = Key::Y;
		io.KeyMap[ImGuiKey_Z] = Key::Z;

		ImGui_ImplOpenGL3_Init("#version 330 core");
		ImGui::StyleColorsDark();
	}

	void ImGuiLayer::OnDetch()
	{
	}

	void ImGuiLayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		auto app = Application::GetInstance();
		io.DisplaySize = ImVec2((float)app->GetWindow().GetWidth(),
			(float)app->GetWindow().GetHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool isShowDemoWindow = true;
		ImGui::ShowDemoWindow(&isShowDemoWindow);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& ev)
	{

		ImGuiIO& io = ImGui::GetIO();
		
		auto evType = ev.GetEventType();
		auto app = Application::GetInstance();
		auto appNativeWin = (GLFWwindow*)(app->GetWindow().GetNativeWindow());
		switch (evType)
		{
		case hazel::EventType::None:
			break;
		case hazel::EventType::WindowClose:
			break;
		case hazel::EventType::WindowResize:
			break;
		case hazel::EventType::WindowFocus:
			break;
		case hazel::EventType::WindowLostFocus:
			break;
		case hazel::EventType::WindowMoved:
			break;
		case hazel::EventType::AppTick:
			break;
		case hazel::EventType::AppUpdate:
			break;
		case hazel::EventType::AppRender:
			break;
		case hazel::EventType::KeyPressed:
		{
			io.KeysDown[((KeyPressedEvent*)(&ev))->GetKeyCode()] = true;
			io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
			io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
			io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
#ifdef _WIN32
			io.KeySuper = false;
#else
			io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
#endif
		}
		break;
		case hazel::EventType::KeyReleased:
			break;
		case hazel::EventType::KeyTyped:
		{

		}
		break;
		case hazel::EventType::MouseButtonPressed:
		{
			auto mouseEv = (MouseButtonReleasedEvent*)(&ev);
			for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++)
			{
				// If a mouse press event came, always pass it as "mouse held this frame", so we don't miss click-release events that are shorter than 1 frame.
				io.MouseDown[i] = (i == ((MouseButtonPressedEvent*)(&ev))->GetMouseButton())
					? true : false;
			}
			const bool focused = glfwGetWindowAttrib(appNativeWin, GLFW_FOCUSED) != 0;
			if (focused)
			{
				if (io.WantSetMousePos)
				{
					glfwSetCursorPos(appNativeWin, (double)mouseEv.Get.x, (double)mouse_pos_backup.y);
				}
				else
				{
					double mouse_x, mouse_y;
					glfwGetCursorPos(appNativeWin, &mouse_x, &mouse_y);
					io.MousePos = ImVec2((float)mouse_x, (float)mouse_y);
				}
			}
		}
			break;
		case hazel::EventType::MouseButtonReleased:
			break;
		case hazel::EventType::MouseMoved:
			break;
		case hazel::EventType::MouseScrolled:
			break;
		default:
			break;
		}
	}
}
