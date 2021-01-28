#pragma once

#include "../Core/Core.h"

namespace hazel {

	// Events in Hazel are currently blocking, meaning when an event occurs it
	// immediately gets dispatched and must be dealt with right then an there.
	// For the future, a better strategy might be to buffer events in an event
	// bus and process them during the "event" part of the update stage.

	/// <summary>
	/// All type of event
	/// </summary>
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	/// <summary>
	/// 
	/// </summary>
	enum class EventCategory
	{
		None = 0,
		EventCategoryApplication		= BIT(0),
		EventCategoryInput				= BIT(1),
		EventCategoryKeyboard			= BIT(2),
		EventCategoryMouse				= BIT(3),
		EventCategoryMouseButton		= BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class Event
	{
	public:

		virtual ~Event() = default;

		/// <summary>
		/// Get EventType
		/// </summary>
		/// <returns>EventType</returns>
		virtual EventType GetEventType() const = 0;

		/// <summary>
		/// Get 
		/// </summary>
		/// <returns></returns>
		virtual int GetCategoryFlags() const = 0;

#ifdef HZ_DEBUG

		/// <summary>
		/// Get name as char*
		/// </summary>
		/// <returns></returns>
		virtual const char* GetName() const = 0;

		/// <summary>
		/// Get string of name
		/// </summary>
		/// <returns></returns>
		virtual std::string ToString() const { return GetName(); }

#endif // HZ_DEBUG

		/// <summary>
		/// Is the ev catagory right 
		/// </summary>
		/// <param name="category"></param>
		/// <returns></returns>
		bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & static_cast<int>(category);
		}

		/// <summary>
		/// Has been handled
		/// </summary>
		bool Handled = false;

	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		// F will be deduced by the compiler
		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled |= func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}

}