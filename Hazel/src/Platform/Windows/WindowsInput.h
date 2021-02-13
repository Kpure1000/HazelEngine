#pragma once

#include "Hazel/Core/Input.h"

namespace hazel
{
	class WindowsInput : public Input
	{
	protected:

		virtual bool IsKeyPressedImpl(KeyCode keyCode) override;

		virtual bool IsMouseButtonPressedImpl(MouseCode mCode) override;
		
		virtual float GetMousePosXImpl() override;
		virtual float GetMousePosYImpl() override;
		virtual std::pair<float, float> GetMousePosImpl() override;
		
		virtual float GetMouseWheelHImpl() override;
		virtual float GetMouseWheelVImpl() override;
	};
}

