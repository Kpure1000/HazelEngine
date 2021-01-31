#pragma once

#include "Hazel/Core/Core.h"
#include "Hazel/Core/KeyCodes.h"
#include "Hazel/Core/MouseCodes.h"
#include "Hazel/Utility/Singleton.h"
#include <memory>

namespace hazel
{
	class HAZEL_API Input
	{
	public:
		static bool IsKeyPressed(KeyCode keyCode) { return m_Instance->IsKeyPressedImpl(keyCode); }

		static bool IsMouseButtonPressed(MouseCode mCode) { return m_Instance->IsMouseButtonPressedImpl(mCode); }

		static float GetMousePosX() { return m_Instance->GetMousePosXImpl(); }
		static float GetMousePosY() { return m_Instance->GetMousePosYImpl(); }
		static std::pair<float, float> GetMousePos() { return m_Instance->GetMousePosImpl(); }

		static float GetMouseWheelH() { return m_Instance->GetMouseWheelHImpl(); }
		static float GetMouseWheelV() { return m_Instance->GetMouseWheelVImpl(); }
	protected:
		virtual bool IsKeyPressedImpl(KeyCode keyCode) = 0;

		virtual bool IsMouseButtonPressedImpl(MouseCode mCode) = 0;

		virtual float GetMousePosXImpl() = 0;
		virtual float GetMousePosYImpl() = 0;
		virtual std::pair<float, float> GetMousePosImpl() = 0;

		virtual float GetMouseWheelHImpl() = 0;
		virtual float GetMouseWheelVImpl() = 0;

	private:

		static std::shared_ptr<Input> m_Instance;

	};

}