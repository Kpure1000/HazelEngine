#pragma once

#include "Hazel/Core/Core.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/KeyEvent.h"

#include "Renderer/Camera/OrthographicCamera.h"

namespace hazel
{
	class HAZEL_API OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRotiom, bool rotation = false, bool moveFollowZoom = false);

		void OnUpdate();
		void OnEvent(Event& ev);

		inline OrthographicCamera& GetCamera() { return *m_Camera; }
		inline const OrthographicCamera& GetCamera()const { return *m_Camera; }

		inline void EnableInput(bool enable) { m_EnableInput = enable; }
		inline void EnableMove(bool enable) { m_EnableMove = enable; }
		inline void EnableZoom(bool enable) { m_EnableZoom = enable; }

		/// <summary>
		/// Set zoom immediatly
		/// </summary>
		/// <param name="zoom">New zoom</param>
		void SetZoom(float zoom);

		/// <summary>
		/// Set zoom smoothing
		/// </summary>
		/// <param name="zoom">New zoom</param>
		void SetSmoothZoom(float zoom);

	private:
		void GetTranslateInput();
		void GetRotateInput();

		bool OnMouseScrolled(MouseScrolledEvent& ev);
		bool OnWindowResized(WindowResizeEvent& ev);

	private:
		float m_AspectRatio;
		float m_ZoomLevel;
		float m_NewZoom;

		float m_MoveSpeed;
		float m_RotateSpeed;
		float m_ScaleSpeed;

		float vel = 0.0f;
		
		bool m_EnableInput;
		bool m_EnableMove;
		bool m_EnableZoom;
		bool m_EnableRotate;
		bool m_MoveFollowZoom;

		Ref<OrthographicCamera> m_Camera;

	private:
		glm::vec3 tmpTranslation;
		float tmpRotateion;

	};
}