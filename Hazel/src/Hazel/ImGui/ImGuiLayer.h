#pragma once

#include "Hazel/Core/Layer.h"

#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/ApplicationEvent.h"

namespace hazel
{
	class HAZEL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetch() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time;

	};
}
