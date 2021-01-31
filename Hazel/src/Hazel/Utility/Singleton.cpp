#include "hzpch.h"

#include "Singleton.h"

namespace hazel
{
	template<typename T>
	std::shared_ptr<T> Singleton<T>::m_instance_ = nullptr;

	template<typename T>
	T* Singleton<T>::GetInstance()
	{
		static std::mutex m_mutex;
		if (nullptr == m_instance_) {
			std::lock_guard<std::mutex> lock(m_mutex);
			if (nullptr == m_instance_) {
				m_instance_ = std::make_shared<T>();
			}
		}
		return m_instance_.get();
	}
}
