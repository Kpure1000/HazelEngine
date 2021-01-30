#pragma once

#include "Hazel/Core/Core.h"
#include "Hazel/Layer.h"

namespace hazel
{
	class HAZEL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach()override;
		void OnDetch() override;
		void OnUpdate()override;
		void OnEvent(Event& ev) override;

	private:
		float m_Time;

	};
}
