#pragma once

#include "../Core/Core.h"

#include <mutex>
#include <memory>

namespace krt {

	template<typename T>
	class KRT_API Singleton {
	public:
		template<typename ...Args>
		static std::shared_ptr<T> GetInstance(Args&&... args) {
			if (!m_Instance) {
				std::lock_guard<std::mutex> gLock(m_Mutex);
				if (nullptr == m_Instance) {
					m_Instance = std::make_shared<T>(std::forward<Args>(args)...);
				}
			}
			return m_Instance;
		}

		static void Destroy() {
			if (m_Instance) {
				m_Instance.reset();
				m_Instance = nullptr;
			}
		}

	private:
		explicit Singleton();
		Singleton(const Singleton&) = delete;
		Singleton& operator=(const Singleton&) = delete;
		//~Singleton();

	private:
		static std::shared_ptr<T> m_Instance;
		static std::mutex m_Mutex;
	};

	template<typename T>
	std::shared_ptr<T> Singleton<T>::m_Instance = nullptr;

	template<typename T>
	std::mutex Singleton<T>::m_Mutex;

}