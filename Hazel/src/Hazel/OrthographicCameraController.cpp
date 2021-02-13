#include "hzpch.h"

#include "OrthographicCameraController.h"

#include "Hazel/Time.h"
#include "Hazel/Input.h"
#include "Hazel/Log.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace hazel
{

	static float SmoothDamp(float current, float target,
		float& velocity, float smoothTime,
		float maxSpeed = FLT_MAX, float deltaTime = Time::deltaTime())
	{
		smoothTime = glm::max(0.0001f, smoothTime);
		float num = 2.0f / smoothTime;
		float num2 = num * deltaTime;
		float num3 = 1.0f / (1.0f + num2 + 0.48f * num2 * num2 + 0.245f * num2 * num2 * num2);
		float num4 = current - target;
		float num5 = target;
		float num6 = maxSpeed * smoothTime;
		num4 = glm::clamp(num4, -num6, num6);
		target = current - num4;
		float num7 = (velocity + num * num4) * deltaTime;
		float num8 = target + (num4 + num7) * num3;
		if (num5 - current > 0.0f == num8 > num5)
		{
			num8 = num5;
			velocity = (num8 - num5) / deltaTime;
		}
		return num8;
	}

	static glm::vec3 SmoothDamp(const glm::vec3& current, const glm::vec3& target,
		glm::vec3& velocity, float smoothTime,
		const glm::vec3& maxSpeed = { FLT_MAX,FLT_MAX,FLT_MAX }, float deltaTime = Time::deltaTime())
	{
		return { SmoothDamp(current.x, target.x, velocity.x, smoothTime, maxSpeed.x, deltaTime),
			SmoothDamp(current.y, target.y, velocity.y, smoothTime, maxSpeed.y, deltaTime),
		SmoothDamp(current.z, target.z, velocity.z, smoothTime, maxSpeed.z, deltaTime) };
	}

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

		m_ZoomLevel = SmoothDamp(m_ZoomLevel, m_NewZoom, vel, 0.2f, 1000.0f, Time::deltaTime() * m_ScaleSpeed);

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