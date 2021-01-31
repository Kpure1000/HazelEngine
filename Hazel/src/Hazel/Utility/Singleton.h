#pragma once
#include "Hazel/Core/Core.h"
#include <memory>
namespace hazel
{
	template<typename T>
	class HAZEL_API Singleton {
	public:
		static T* GetInstance();

	private:

		static std::shared_ptr<T> m_instance_;
	};


}