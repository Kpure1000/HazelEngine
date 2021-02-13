#include "hzpch.h"

#include "OrthographicCameraController.h"

#include "Hazel/Time.h"
#include "Hazel/Input.h"
#include "Hazel/Log.h"

#include "Hazel/Utility/Math.h"

namespace hazel
{
	OrthographicCameraController::OrthographicCameraController(float aspectRotio, bool rotation)
		: m_AspectRatio(aspectRotio), m_ZoomLevel(1.0f), m_NewZoom(m_ZoomLevel),
		m_MoveSpeed(5.0f), m_RotateSpeed(20.0f), m_ScaleSpeed(5.0f),
		m_EnableRotate(rotation),
		m_Camera(std::make_shared< OrthographicCamera>(
			glm::vec2(-m_AspectRatio * m_ZoomLevel, -m_ZoomLevel),
			glm::vec2(m_AspectRatio* m_ZoomLevel, m_ZoomLevel)
			)),
		tmpTranslation(0.0f), tmpRotateion(0.0f)
	{
	}

	void OrthographicCameraController::OnUpdate()
	{
		//  Logic update
		tmpTranslation.x = tmpTranslation.y = tmpTranslation.x = 0.0f;
		tmpRotateion = 0.0f;
		if (Input::IsKeyPressed(Key::A))tmpTranslation.x -= m_MoveSpeed * Time::deltaTime();
		if (Input::IsKeyPressed(Key::D))tmpTranslation.x += m_MoveSpeed * Time::deltaTime();
		if (Input::IsKeyPressed(Key::W))tmpTranslation.y += m_MoveSpeed * Time::deltaTime();
		if (Input::IsKeyPressed(Key::S))tmpTranslation.y -= m_MoveSpeed * Time::deltaTime();
		m_Camera->SetPosition(m_Camera->GetPosition() + tmpTranslation);

		if (m_EnableRotate)
		{
			if (Input::IsKeyPressed(Key::Q))tmpRotateion += m_RotateSpeed * Time::deltaTime();
			if (Input::IsKeyPressed(Key::E))tmpRotateion -= m_RotateSpeed * Time::deltaTime();
			m_Camera->SetRotation(m_Camera->GetRotation() + tmpRotateion);
		}

		m_ZoomLevel = Math::SmoothDamp(m_ZoomLevel, m_NewZoom, vel, 0.2f, 1000.0f, Time::deltaTime() * m_ScaleSpeed);

		m_Camera->SetProjection(
			glm::vec2(-m_AspectRatio * m_ZoomLevel, -m_ZoomLevel),
			glm::vec2(m_AspectRatio* m_ZoomLevel, m_ZoomLevel)
		);
	}

	void OrthographicCameraController::OnEvent(Event& ev)
	{
		EventDispatcher dispatcher(ev);
		dispatcher.Dispatch<MouseScrolledEvent>(HZ_BIND_EVENT_FN(OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& ev)
	{
		Log::TraceCore("zoom: {0}", m_NewZoom);
		m_NewZoom = glm::clamp(m_NewZoom - ev.GetYOffset() * 0.1f, 0.2f, 10.0f);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& ev)
	{
		return false;
	}
}