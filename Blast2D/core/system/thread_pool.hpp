#ifndef THREAD_POOL
#define THREAD_POOL

#include <vector>
#include <thread>
#include <memory>
#include <future>
#include <functional>
#include <queue>
#include <condition_variable>

#include <core/logging/easylogging++.h>

namespace Blast2D {
	class ThreadPool {
	private:
		std::vector<std::thread> threads;
		std::mutex pool_mutex;
		std::condition_variable condition_run;
		std::condition_variable condition_add;
		std::queue<std::function<void()>> tasks;
		bool running = true;
		unsigned int limit = 0;
	public:
		void infiniteLoop() {

			std::unique_lock<std::mutex> queue_lock(pool_mutex, std::defer_lock);

			while (true) {
				queue_lock.lock();
				condition_run.wait(queue_lock, [this]() {return !this->tasks.empty() || !running; });

				if (!running) return;

				auto func = std::move(tasks.front());
				tasks.pop();
				//condition_add.notify_one();
				queue_lock.unlock();				
				func();
			}
		}

		void addTask(std::function<void()> task) {
			std::unique_lock<std::mutex> queue_lock(pool_mutex, std::defer_lock);			
			queue_lock.lock();
			//condition_add.wait(queue_lock, [this]() {return this->tasks.size() < limit || !running; });
			tasks.push(task);
			condition_run.notify_one();
			queue_lock.unlock();
		}

		ThreadPool() {
			limit = std::thread::hardware_concurrency();
			for (auto i = 0; i < limit; ++i) {
				threads.push_back(std::thread(&ThreadPool::infiniteLoop, this));
			}
		}

		~ThreadPool() {
			running = false;
			condition_run.notify_all();
			for (std::thread& thread : threads) {				
				thread.join();
			}
		}
	};
}
#endif // !THREAD_POOL


