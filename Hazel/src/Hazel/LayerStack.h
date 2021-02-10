#pragma once

#include <vector>
#include <memory>

#include "Layer.h"

namespace hazel
{
	class HAZEL_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Ref<Layer> layer);
		void PushOverLay(Ref<Layer> overLay);
		void PopLayer(Ref<Layer> layer);
		void PopOverLay(Ref<Layer> overLay);

		std::vector<Ref<Layer>>::iterator begin() { return m_Layers.begin(); }
		std::vector<Ref<Layer>>::iterator end() { return m_Layers.end(); }

	private:
		std::vector<Ref<Layer>> m_Layers;
		unsigned int m_LayerStackIndex = 0;


	};
}

