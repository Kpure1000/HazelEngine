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

		void PushLayer(std::shared_ptr<Layer> layer);
		void PushOverLay(std::shared_ptr<Layer> overLay);
		void PopLayer(std::shared_ptr<Layer> layer);
		void PopOverLay(std::shared_ptr<Layer> overLay);

		std::vector<std::shared_ptr<Layer>>::iterator begin() { return m_Layers.begin(); }
		std::vector<std::shared_ptr<Layer>>::iterator end() { return m_Layers.end(); }

	private:
		std::vector<std::shared_ptr<Layer>> m_Layers;
		unsigned int m_LayerStackIndex = 0;


	};
}

