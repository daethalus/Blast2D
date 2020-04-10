#include <iostream>
#include <logging/easylogging++.h>
#include <logging/chronometer.hpp>
#include <ecs/entity_manager.hpp>
#include <ecs/sparse_set.hpp>
#include <ecs/storage.hpp>
#include <functional>

#include <system/thread_pool.hpp>

#include <queue>

INITIALIZE_EASYLOGGINGPP


struct Position {
	int x;
};

struct Velocity {
	int y;
};


int main() {	

	ThreadPool tp;

	LOG(INFO) << "Starting engine";
	Blast2D::EntityManager entityManager;
	entityManager.createComponent<Position>();
	entityManager.createComponent<Velocity>();	

	auto chrono = Blast2D::Chronometer::create();

	for (int x = 999999; x >= 0; --x) {
		auto entity = entityManager.create();
		entityManager.set<Position>(entity, { x });
		entityManager.set<Velocity>(entity, { x });		
	}
	long long a = 0;

	chrono.lap();

	tp.addTask([&entityManager, &a]() {
		for (int x = 9999999; x >= 0; --x) {
			a = a * x;
		}
	});

	chrono.lap();

	entityManager.forEach<Position, Velocity>([](auto& position, auto& velocity) {
		//LOG(INFO) << position.x;		
	});



	chrono.end();

	std::string aaa;
	std::cin >> aaa;
}
