#include "hzpch.h"

#include "LayerStack.h"
#include <stack>
namespace hazel
{
	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack()
	{
	}

	void hazel::LayerStack::PushLayer(std::shared_ptr<Layer> layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerStackIndex, layer);
		m_LayerStackIndex++;
	}

	void hazel::LayerStack::PushOverLay(std::shared_ptr<Layer> overLay)
	{
		m_Layers.emplace_back(overLay);
	}

	void hazel::LayerStack::PopLayer(std::shared_ptr<Layer> layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayerStackIndex--;
		}
	}

	void hazel::LayerStack::PopOverLay(std::shared_ptr<Layer> overLay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overLay);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
		}
	}

}
