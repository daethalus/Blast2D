#include <iostream>
#include <logging/easylogging++.h>
#include <logging/chronometer.hpp>
#include <ecs/entity_manager.hpp>
#include <ecs/sparse_set.hpp>
#include <ecs/storage.hpp>
#include <functional>

#include <queue>

INITIALIZE_EASYLOGGINGPP


struct Position {
	int x;
};

struct Velocity {
	int y;
};


int main() {

	LOG(INFO) << "Starting engine";
	Blast2D::EntityManager entityManager;
	entityManager.createComponent<Position>();
	entityManager.createComponent<Velocity>();

	auto chrono = Blast2D::Chronometer::create();

	for (int x = 20; x >= 0; --x) {
		auto entity = entityManager.create();
		entityManager.set<Position>(entity, {x});
		entityManager.set<Velocity>(entity, {x});
	}

	chrono.lap();

	entityManager.forEach<Position, Velocity>([](auto position, auto velocity) {
		LOG(INFO) << position.x;		
	});


	chrono.end();

	std::string aaa;
	std::cin >> aaa;
}
