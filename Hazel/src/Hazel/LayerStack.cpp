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

	void hazel::LayerStack::PushLayer(Ref<Layer> layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerStackIndex, layer);
		m_LayerStackIndex++;
	}

	void hazel::LayerStack::PushOverLay(Ref<Layer> overLay)
	{
		m_Layers.emplace_back(overLay);
	}

	void hazel::LayerStack::PopLayer(Ref<Layer> layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayerStackIndex--;
		}
	}

	void hazel::LayerStack::PopOverLay(Ref<Layer> overLay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overLay);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
		}
	}

}
