#pragma once

#include "Hazel/Core/Core.h"

#include <vector>
#include <queue>

#include <thread>
#include <mutex>
#include <condition_variable>

#include <functional>
#include <type_traits>
#include <future>

#include <memory>

#include <algorithm>

namespace hazel
{
	class HAZEL_API ThreadPool
	{
	public:
		ThreadPool(size_t size)
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

		~ThreadPool()
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

		template<class F, class ... Args>
		decltype(auto) Submit(F&& f, Args&&... args)
		{
			using return_type = std::invoke_result_t<F, Args...>;

			auto task = std::make_shared< std::packaged_task<return_type()> >(
				std::bind(std::forward<F>(f), std::forward<Args>(args)...)
				);
			
			std::future<return_type> result = task->get_future();

			{
				std::unique_lock<std::mutex> lock(_mutex);
				if (isDestroy)
				{
					throw std::runtime_error("Add task on detroyed thread pool");
				}

				m_Tasks.emplace([task]() { (*task)(); });
			}
			_condition.notify_one();
			return result;
		}

	private:
		std::vector<std::thread> m_Threads;
		std::queue<std::function<void()>> m_Tasks;
		std::mutex _mutex;
		std::condition_variable _condition;

		bool isDestroy;

	};
}
