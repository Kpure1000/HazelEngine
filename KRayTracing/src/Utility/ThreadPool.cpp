#include "krtpch.h"
#include "../../include/Utility/ThreadPool.h"

#include <functional>
#include <type_traits>
#include <future>
#include <memory>
#include <algorithm>

using namespace std;

namespace krt {
	ThreadPool::ThreadPool(size_t size)
		:isDestroy(false)
	{
		for (size_t i = 0; i < size; i++)
		{
			m_Threads.emplace_back([this]
				{
					while (true)
					{
						std::function<void()> task;
						{
							//  Get lock
							std::unique_lock<std::mutex> lock(_mutex);
							//  Wait task
							_condition.wait(lock, [this]()
								{
									return this->isDestroy || !this->m_Tasks.empty();
								});
							//  Destroy thread
							if (this->isDestroy && this->m_Tasks.empty())
							{
								return;
							}
							//  Get task
							task = std::move(this->m_Tasks.front());
							this->m_Tasks.pop();
						}
						//  Do task
						task();
					}
				});
		}
	}
	ThreadPool::~ThreadPool()
	{
		{
			std::unique_lock<std::mutex> lock(_mutex);
			isDestroy = true;
		}
		//  Notify all
		_condition.notify_all();
		// Join all
		for_each(m_Threads.begin(), m_Threads.end(), std::mem_fn(&std::thread::join));
	}

}