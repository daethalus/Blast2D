#ifndef THREAD_POOL
#define THREAD_POOL

#include <vector>
#include <thread>
#include <memory>
#include <future>
#include <functional>
#include <queue>
#include <condition_variable>

#include <logging/easylogging++.h>


class ThreadPool {
private:
	std::vector<std::thread> threads;
	std::mutex pool_mutex;
	std::condition_variable condition;
	std::queue<std::function<void()>> tasks;
	bool running = true;
public:

	void infiniteLoop() {

		std::unique_lock<std::mutex> queue_lock(pool_mutex, std::defer_lock);

		while (true) {
			queue_lock.lock();
			condition.wait(queue_lock, [this]() {return !this->tasks.empty() || !running; });

			if (!running) return;

			auto func = std::move(tasks.front());
			tasks.pop();
			queue_lock.unlock();
			func();
		}
	}

	void addTask(std::function<void()> task) {
		std::unique_lock<std::mutex> queue_lock(pool_mutex, std::defer_lock);
		queue_lock.lock();
		tasks.push(task);
		condition.notify_one();
		queue_lock.unlock();
	}

	ThreadPool() {
		auto threadNumber = std::thread::hardware_concurrency();
		for (auto i = 0; i < threadNumber; ++i) {			
			threads.push_back(std::thread(&ThreadPool::infiniteLoop, this));
		}
	}
	~ThreadPool() {
		running = false;
		condition.notify_all();
		for (std::thread& thread : threads) {
			thread.join();
		}
	}
};


#endif // !THREAD_POOL


