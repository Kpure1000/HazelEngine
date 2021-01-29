#pragma once

#include "Hazel/Core/Core.h"
#include "Layer.h"

#include <vector>
#include <memory>


namespace hazel
{
	class HAZEL_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PuahsLayer(std::shared_ptr<Layer> layer);
		void PushOverLay(std::shared_ptr<Layer> overLay);
		void PopLayer(std::shared_ptr<Layer> layer);
		void PopOverLay(std::shared_ptr<Layer> overLay);

		std::vector<std::shared_ptr<Layer>>::iterator begin() { return m_Layers.begin(); }
		std::vector<std::shared_ptr<Layer>>::iterator end() { return m_Layers.end(); }

	private:
		std::vector<std::shared_ptr<Layer>> m_Layers;
		std::vector<std::shared_ptr<Layer>>::iterator m_LayerInsert;


	};
}

