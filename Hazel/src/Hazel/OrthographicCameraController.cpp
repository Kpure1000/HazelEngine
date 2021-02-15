#include "hzpch.h"

#include "OrthographicCameraController.h"

#include "Hazel/Core/Time.h"
#include "Hazel/Core/Input.h"
#include "Hazel/Core/Log.h"

#include "Hazel/Core/Application.h"

#include "Hazel/Utility/Math.h"

namespace hazel
{
	OrthographicCameraController::OrthographicCameraController(float aspectRotio, bool rotation,
		bool moveFollowZoom)
		: m_AspectRatio(aspectRotio), m_ZoomLevel(1.0f), m_NewZoom(m_ZoomLevel),
		m_MoveSpeed(3.0f), m_RotateSpeed(20.0f), m_ScaleSpeed(5.0f),
		m_EnableInput(true), m_EnableRotate(rotation), m_MoveFollowZoom(moveFollowZoom),
		m_Camera(std::make_shared< OrthographicCamera>(
			glm::vec2(-m_AspectRatio * m_ZoomLevel, -m_ZoomLevel),
			glm::vec2(m_AspectRatio* m_ZoomLevel, m_ZoomLevel)
			)),
		tmpTranslation(0.0f), tmpRotateion(0.0f)
	{
	}

	void OrthographicCameraController::OnUpdate()
	{
		//  Get input
		if (m_EnableInput)
		{
			GetTranslateInput();
			if (m_EnableRotate)
			{
				GetRotateInput();
			}
		}

		//  Smooth zoom
		m_ZoomLevel = Math::SmoothDamp(m_ZoomLevel, m_NewZoom, vel, 0.2f, 1000.0f, Time::deltaTime() * m_ScaleSpeed);

		//  Move speed follow zoom
		if (m_MoveFollowZoom)
			m_MoveSpeed = 3.0f * m_ZoomLevel;

		//  Update Camera projection mat
		m_Camera->SetProjection(
			glm::vec2(-m_AspectRatio * m_ZoomLevel, -m_ZoomLevel),
			glm::vec2(m_AspectRatio * m_ZoomLevel, m_ZoomLevel)
		);
	}

	void OrthographicCameraController::OnEvent(Event& ev)
	{
		EventDispatcher dispatcher(ev);
		dispatcher.Dispatch<MouseScrolledEvent>(HZ_BIND_EVENT_FN(OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(OnWindowResized));
	}

	void OrthographicCameraController::SetZoom(float zoom)
	{
		m_NewZoom = m_ZoomLevel = glm::clamp(zoom, 0.2f, 10.0f);
	}

	void OrthographicCameraController::SetSmoothZoom(float zoom)
	{
		m_NewZoom = glm::clamp(zoom, 0.2f, 10.0f);
	}

	void OrthographicCameraController::GetTranslateInput()
	{
		tmpTranslation.x = tmpTranslation.y = tmpTranslation.x = 0.0f;
		tmpRotateion = 0.0f;
		if (Input::IsKeyPressed(Key::A))tmpTranslation.x -= m_MoveSpeed * Time::deltaTime();
		if (Input::IsKeyPressed(Key::D))tmpTranslation.x += m_MoveSpeed * Time::deltaTime();
		if (Input::IsKeyPressed(Key::W))tmpTranslation.y += m_MoveSpeed * Time::deltaTime();
		if (Input::IsKeyPressed(Key::S))tmpTranslation.y -= m_MoveSpeed * Time::deltaTime();
		m_Camera->SetPosition(m_Camera->GetPosition() + tmpTranslation);
	}

	void OrthographicCameraController::GetRotateInput()
	{
		if (Input::IsKeyPressed(Key::Q))tmpRotateion += m_RotateSpeed * Time::deltaTime();
		if (Input::IsKeyPressed(Key::E))tmpRotateion -= m_RotateSpeed * Time::deltaTime();
		m_Camera->SetRotation(m_Camera->GetRotation() + tmpRotateion);
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& ev)
	{
		m_NewZoom = glm::clamp(m_NewZoom - ev.GetYOffset() * Time::deltaTime(), 0.2f, 10.0f);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& ev)
	{
		auto app = Application::GetInstance();
		m_AspectRatio = (float)app->GetWindow().GetSize().x / (float)app->GetWindow().GetSize().y;
		//  Update Camera projection mat
		m_Camera->SetProjection(
			glm::vec2(-m_AspectRatio * m_ZoomLevel, -m_ZoomLevel),
			glm::vec2(m_AspectRatio * m_ZoomLevel, m_ZoomLevel)
		);
		return false;
	}
}