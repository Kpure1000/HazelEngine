#pragma once

#include "Event.h"
#include "../Core/MouseCodes.h"

namespace hazel {

	/// <summary>
	/// Mouse is moving
	/// </summary>
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(const float x, const float y)
			: m_MouseX(x), m_MouseY(y) {}

		/// <summary>
		/// Get pos.x (may be replaced by vec2.x)
		/// </summary>
		/// <returns></returns>
		float GetX() const { return m_MouseX; }

		/// <summary>
		/// Get pos.y (may be replaced by vec2.y)
		/// </summary>
		/// <returns></returns>
		float GetY() const { return m_MouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)

			EVENT_CLASS_CATEGORY(static_cast<int>(EventCategory::EventCategoryMouse) 
				| static_cast<int>(EventCategory::EventCategoryInput))

	private:
		float m_MouseX, m_MouseY;
	};

	/// <summary>
	/// Mouse wheel is scrolling
	/// </summary>
	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(const float xOffset, const float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		float GetXOffset() const { return m_XOffset; }
		float GetYOffset() const { return m_YOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)

			EVENT_CLASS_CATEGORY(static_cast<int>(EventCategory::EventCategoryMouse)
				| static_cast<int>(EventCategory::EventCategoryInput))

	private:
		float m_XOffset, m_YOffset;
	};

	/// <summary>
	/// Mouse button is BEING pressed
	/// </summary>
	class MouseButtonEvent : public Event
	{
	public:
		MouseCode GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(static_cast<int>(EventCategory::EventCategoryMouse)
			| static_cast<int>(EventCategory::EventCategoryInput)
			| static_cast<int>(EventCategory::EventCategoryMouseButton))
		
	protected:
		MouseButtonEvent(const MouseCode button)
			: m_Button(button) {}

		MouseCode m_Button;
	};

	/// <summary>
	/// Mouse button was EVEN pressed at least once
	/// </summary>
	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(const MouseCode button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)

	};

	/// <summary>
	/// Mouse button was released after pressed
	/// </summary>
	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(const MouseCode button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)

	};

}
