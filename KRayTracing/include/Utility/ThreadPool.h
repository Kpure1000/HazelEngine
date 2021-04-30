#pragma once

#include "../Core/Core.h"

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

namespace krt {

	class KRT_API ThreadPool {
	public:
		ThreadPool(size_t size);

		~ThreadPool();
		
		template<class F, class ... Args>
		decltype(auto) Submit(F&& f, Args&&... args);
		
		inline size_t GetThreadSize() const {
			return m_Threads.size();
		}

		inline size_t GetTaskSize() const {
			return m_Tasks.size();
		}

	private:
		std::vector<std::thread> m_Threads;
		std::queue<std::function<void()>> m_Tasks;
		mutable std::mutex _mutex;
		std::condition_variable _condition;

		bool isDestroy;
	};

	template<class F, class ...Args>
	inline decltype(auto) ThreadPool::Submit(F&& f, Args && ...args) {
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

			//  add task
			m_Tasks.emplace([task]() { (*task)(); });
		}
		_condition.notify_one();
		return result;
	}

}
